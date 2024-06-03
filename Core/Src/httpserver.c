
/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "string.h"
#include "httpserver.h"
#include "cmsis_os.h"
#include "tcp_defines.h"

int indx = 0;

static void http_server(struct netconn *conn)
{
	struct netbuf *inbuf;
	err_t recv_err;
	char* buf;
	u16_t buflen;
	struct fs_file file;

	char pagedata[512]={0};
	char response_int[10]={0};

	/* Read the data from the port, blocking if nothing yet there */
	recv_err = netconn_recv(conn, &inbuf);

	if (recv_err == ERR_OK)
	{
		if (netconn_err(conn) == ERR_OK)
		{
			/* Get the data pointer and length of the data inside a netbuf */
			netbuf_data(inbuf, (void**)&buf, &buflen);
			if (strncmp((char const *)buf,"GET /getvalue",13)==0)
			{

				int len_pagedata = 0;
				len_pagedata += sprintf((char *)pagedata, "HTTP/1.1 200 OK\r\n");
				int len = sprintf (response_int, "%d", indx++);
				len_pagedata += strncat((char*)pagedata, "Content-Length: %d\r\n", len);
				len_pagedata += strcat((char *)pagedata, "Content-Type: text/plain; charset=utf-8\r\n\r\n");
				len_pagedata += strcat((char*)pagedata, response_int);


				int netconn_rv = netconn_write(conn, (const unsigned char*)pagedata, strlen((char*)pagedata), NETCONN_COPY);
			}
		}
	}
	/* Close the connection (server closes in HTTP) */
	netconn_close(conn);

	/* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
	netbuf_delete(inbuf);
}


static void http_thread(void *arg)
{ 
	struct netconn *newconn;
	err_t err, accept_err;

	if (conn!= NULL)
	{
		if (netconn_bind_err == ERR_OK)
		{
			/* Put the connection into LISTEN state */
			netconn_listen(conn);

			while(1)
			{
				/* accept any incoming connection */
				accept_err = netconn_accept(conn, &newconn);
				if(accept_err == ERR_OK)
				{
					/* serve connection */
					http_server(newconn);

					/* delete connection */
					netconn_delete(newconn);
				}
			}
		}
	}
}


void http_server_init(void)
{
	sys_thread_new("http_thread", http_thread, NULL, DEFAULT_THREAD_STACKSIZE >> 1, osPriorityNormal);
}


