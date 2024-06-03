/* Includes ------------------------------------------------------------------*/
#include <app_defines.h>
#include "lwip/opt.h"

#include "lwip/api.h"
#include "lwip/sys.h"

#include "http_client.h"

#include "string.h"
#include <cJSON.h>
#include <rest_api_client.h>

struct netconn *conn;
err_enum_t netconn_bind_err;

static ip_addr_t dest_addr;
char msg_rest_api[512];
char pv_estimate[16];
uint8_t IP_ADDRESS_SERVER[4] = {192, 168, 0, 171};
const char REST_API_SERVER[150] = "/rooftop_sites/e5cc-f38e-7730-805d/estimated_actuals?api_key=u70RlALYTh-bWi9lDsuRKxWWi3jQApLz&format=json&hours=1";
const uint16_t DEST_PORT_SERVER = 10;

typedef enum
{
	PARSE_OK = 0,
	PARSE_ERR = -1
} parse_result_t;


typedef enum
{
	EST_PLAUSIBLE = 0,
	EST_NOT_PLAUSIBLE = -1
} est_plausible_t;


est_plausible_t pv_estimate_is_plausible(double pv_estimate)
{
	if((pv_estimate > 0) && (pv_estimate < 2))
	{
		return EST_PLAUSIBLE;
	}
	else
	{
		return EST_NOT_PLAUSIBLE;
	}
}


static parse_result_t get_pv_estimate(const char * const read_msg_rest_api, char * parsed_pv_estimate)
{
	const cJSON *estimate = NULL;
	const cJSON *pv_estimated_actuals = NULL;

	cJSON *parsed_json = cJSON_Parse(read_msg_rest_api);
	if (parsed_json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			cJSON_Delete(parsed_json);
			return PARSE_ERR;
		}
	}
	pv_estimated_actuals = cJSON_GetObjectItemCaseSensitive(parsed_json, "estimated_actuals");
	cJSON_ArrayForEach(estimate, pv_estimated_actuals)
	{
		cJSON *pv_estimate = cJSON_GetObjectItemCaseSensitive(estimate, "pv_estimate");

		if (!cJSON_IsNumber(pv_estimate))
		{
			cJSON_Delete(parsed_json);
			return PARSE_ERR;
		}

		if (pv_estimate_is_plausible(pv_estimate->valuedouble) == EST_PLAUSIBLE)
		{
			cJSON_Delete(parsed_json);
			sprintf(parsed_pv_estimate, "%.3f", 1000*pv_estimate->valuedouble);
			return PARSE_OK;
		}
		else
		{
			cJSON_Delete(parsed_json);
			return PARSE_ERR;
		}
	}

	return PARSE_ERR;
}



err_t my_http_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	for(uint16_t i=0;i<p->len;i++)
	{
		strncpy (msg_rest_api, p->payload, p->len);
	}
	pbuf_free(p);
	get_pv_estimate(msg_rest_api, pv_estimate);
	return ERR_OK;
}


void my_httpc_result_fn(void *arg, httpc_result_t httpc_result, u32_t rx_content_len, u32_t srv_res, err_t err)
{
	asm("NOP");
}


err_t my_httpc_headers_done_fn(httpc_state_t *connection, void *arg, struct pbuf *hdr, u16_t hdr_len, u32_t content_len)
{
	return ERR_OK;
}


static void rest_api_client_thread(void *arg)
{
	httpc_connection_t http_settings;
	httpc_state_t *connection;

	if (netconn_bind_err == ERR_OK)
	{
		/* The designation IP address of the computer */
		IP_ADDR4(&dest_addr, IP_ADDRESS_SERVER[0], IP_ADDRESS_SERVER[1], IP_ADDRESS_SERVER[2], IP_ADDRESS_SERVER[3]);
		while (1)
		{
			osSignalWait(0x1, 1*1000);
			memset (msg_rest_api, '\0', 512);  // clear the buffer
			http_settings.use_proxy =0;
			http_settings.result_fn = my_httpc_result_fn;
			http_settings.headers_done_fn = my_httpc_headers_done_fn;
			httpc_get_file(&dest_addr, DEST_PORT_SERVER, REST_API_SERVER, &http_settings, my_http_cb, 0, &connection);
		}
	}
	else
	{
		// if the binding wasn't successful, delete the netconn connection
		netconn_delete(conn);
	}
}


void tcpclient_init (void)
{
	sys_thread_new("rest_api_client_thread", rest_api_client_thread, NULL, DEFAULT_THREAD_STACKSIZE >> 1,osPriorityNormal);
}

