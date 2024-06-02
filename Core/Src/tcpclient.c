/*
 * tcpclient.c
 *
 *  Created on: 21-Apr-2022
 *      Author: controllerstech
 */


#include "lwip/opt.h"

#include "lwip/api.h"
#include "lwip/sys.h"

#include "tcpclient.h"
#include "http_client.h"

#include "string.h"

static struct netconn *conn;
static ip_addr_t dest_addr;
static unsigned short port, dest_port;
char msg_rest_api[512];


err_t my_http_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	for(uint16_t i=0;i<p->len;i++)
	{
		strncpy (msg_rest_api, p->payload, p->len);
	}
	pbuf_free(p);
	return ERR_OK;
}


void my_httpc_result_fn(void *arg, httpc_result_t httpc_result, u32_t rx_content_len, u32_t srv_res, err_t err)
{

}


err_t my_httpc_headers_done_fn(httpc_state_t *connection, void *arg, struct pbuf *hdr, u16_t hdr_len, u32_t content_len)
{
	return ERR_OK;
}


static void tcpinit_thread(void *arg)
{
	err_t err;
	httpc_connection_t http_settings;
	httpc_state_t *connection;
	const char rest_api_uri[150] = "/rooftop_sites/e5cc-f38e-7730-805d/estimated_actuals?api_key=u70RlALYTh-bWi9lDsuRKxWWi3jQApLz&format=json&hours=1";


	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);

	err = netconn_bind(conn, IP_ADDR_ANY, 7 /*62510*/);
	if (err == ERR_OK)
	{
		/* The desination IP adress of the computer */
		IP_ADDR4(&dest_addr, 192, 168, 0, 171);
		dest_port = 10;  // server port
		while (1)
		{
			//osSignalWait(0x1, osWaitForever);
			osSignalWait(0x1, 1*1000);
			memset (msg_rest_api, '\0', 512);  // clear the buffer
			http_settings.use_proxy =0;
			http_settings.result_fn = my_httpc_result_fn;
			http_settings.headers_done_fn = my_httpc_headers_done_fn;
			httpc_get_file(&dest_addr, 10, rest_api_uri, &http_settings, my_http_cb, 0, &connection);

			//		for(;;)
			//		{
			//			osDelay(1);
			//		}
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
	sys_thread_new("tcpinit_thread", tcpinit_thread, NULL, DEFAULT_THREAD_STACKSIZE,osPriorityNormal);
}

