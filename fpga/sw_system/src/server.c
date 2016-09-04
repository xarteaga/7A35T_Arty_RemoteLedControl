#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include <sys/types.h>


#include "server.h"

#include "lwip/err.h"
#include "lwip/tcp.h"

#define VERBOSE

extern resource_t resources[];

void print_app_header()
{
	xil_printf("\n\r\n\r----- VaXi'S Server V. 1.0.a ------\n\r");
	xil_printf("Compiled date: %s\n\r", __DATE__);
	xil_printf("Compiled time: %s\n\r", __TIME__);
}

int readMethodFromBuffer (char * buffer, uint16_t size, uint8_t *method) {
	uint16_t offset = 0;

	while (buffer[offset] != ' ' && offset < size) {
		offset++;
	}

	if (offset == size)
		return -1;

	if (strncmp(buffer, "GET", 3) == 0) {
		*method = REQ_GET;
	} else {
		return -1;
	}

	return ++offset;
}

int readPathFromBuffer(char * buffer, uint16_t size, int offset, char *path) {
	int pathLen = 0;
	int begin = offset;

	while (buffer[offset] != '?' && buffer[offset] != ' ' && offset < size) {
		++offset;
		++pathLen;
	}

	if (offset == size)
		return -1;

	if (pathLen > 1 && buffer[offset - 1] == '/')
		pathLen--;

	strncpy(path, (buffer + begin), pathLen);
	path[pathLen] = 0;

	printf(path);

	return ++offset;
}

int readParamFromBuffer(char * buffer, uint16_t size, int offset, param_t *param){
	int begin_name = offset, len_name, begin_value, len_value;

	while (buffer[offset] != '=' && offset < size) {
		++offset;
	}

	len_name = offset - begin_name;
	begin_value = offset + 1;

	if (offset == size)
		return -1;

	while (buffer[offset] != '&' && buffer[offset] != ' ' && offset < size) {
		++offset;
	}
	len_value = offset - begin_value;

	if (offset == size)
		return -1;

	strncpy(param->name, &buffer[begin_name], len_name);
	param->name[len_name] = 0;

	strncpy(param->value, &buffer[begin_value], len_value);
	param->value[len_value] = 0;

	return ++offset;
}

int readParamsFromBuffer(char * buffer, uint16_t size, int offset, param_t *params){

	uint8_t count = 0;

	while(offset > 0 && offset < size && buffer[offset - 1] != ' ' && count < MAX_PARAMS){
		offset = readParamFromBuffer(buffer, size, offset, &params[count]);
		++count;
	}

	if (offset == size)
		return -1;

	while(offset > 0 && offset < size && buffer[offset] != '\n'){
		++offset;
	}

	if (offset == size)
		return -1;

	return ++offset;
}

int readHeaderFromBuffer(char * buffer, uint16_t size, uint16_t offset, header_t *header){
	int begin_name = offset, len_name, begin_value, len_value;

	while (buffer[offset] != ':' && offset < size) {
		++offset;
	}

	len_name = offset - begin_name;
	begin_value = offset + 2;

	if (offset == size)
		return -1;

	while (buffer[offset] != '\n' && offset < size) {
		++offset;
	}
	len_value = offset - begin_value;

	if (offset == size)
		return -1;

	strncpy(header->name, &buffer[begin_name], len_name);
	header->name[len_name] = 0;

	strncpy(header->value, &buffer[begin_value], len_value);
	header->value[len_value] = 0;

	return ++offset;
}

int readHeadersFromBuffer(char * buffer, uint16_t size, uint16_t offset, header_t *headers){

	uint8_t count = 0;

	while(offset > 0 && offset < size && buffer[offset] != '\n'&& count < MAX_HEADERS){
		offset = readHeaderFromBuffer(buffer, size, offset, &headers[count]);
		++count;
	}

	while(offset > 0 && offset < size && buffer[offset] != '\n'){
		++offset;
	}

	if (offset == size)
		return -1;

	return ++offset;
}

int parse_request(char *buffer, uint16_t len, request_t *req) {
	int offset = readMethodFromBuffer(buffer, len, &req->code);
	if (offset < 0) {
		printf("ERROR reading method\r\n");
		return -1;
	}

	offset = readPathFromBuffer(buffer, len, offset, req->url);
	if (offset < 0) {
		printf("ERROR reading Path\r\n");
		return -1;
	}

	offset = readParamsFromBuffer(buffer, len, offset, req->params);
	if (offset < 0) {
		printf("ERROR reading URL parameters\r\n");
		return -1;
	}

	offset = readHeadersFromBuffer(buffer, len, offset, req->headers);
	if (offset < 0) {
		printf("ERROR reading Headers\r\n");
		return -1;
	}

	return offset;
}

int send_response (struct tcp_pcb *tpcb, response_t *res) {
	int n, err, i;
	char buffer [1024];

	if (res->code == RES_OK) {
		n = sprintf(buffer, "HTTP 200 OK\r\nContent-Length: %u\r\n", (unsigned int) res->content_length);
	} else /*if (res->code == RES_REDIRECT)*/{
		n = sprintf(buffer, "HTTP/1.1 307 Temporary Redirect\r\n");
	}

	for(i = 0; strlen(res->headers[i].name) > 0; i++){
		n += sprintf(buffer + n, "%s : %s\r\n", res->headers[i].name, res->headers[i].value);
	}
	n += sprintf(buffer + n, "\r\n");
    xil_printf(buffer);

	if (tcp_sndbuf(tpcb) > n) {
			err = tcp_write(tpcb, buffer, n, 1);
	} else {
		xil_printf("no space in tcp_sndbuf\n\r");
		return -1;
	}

	if (tcp_sndbuf(tpcb) > n) {
		err = tcp_write(tpcb, res->content, res->content_length, 1);
		n += res->content_length;
	} else {
		xil_printf("no space in tcp_sndbuf\n\r");
		return -1;
	}



	return 0;
}

err_t recv_callback(void *arg, struct tcp_pcb *tpcb,
                               struct pbuf *p, err_t err)
{
	request_t req;
	response_t res;
	memset(&req, 0, sizeof(request_t));
	char strbuf[1024];
	uint32_t i;

	/* do not read the packet if we are not in ESTABLISHED state */
	if (!p) {
		tcp_close(tpcb);
		tcp_recv(tpcb, NULL);
		return ERR_OK;
	}

	/* indicate that the packet has been received */
	tcp_recved(tpcb, p->len);

	memcpy(strbuf, p->payload, p->len);
	strbuf[p->len] = 0;
	//printf("[ BEGIN size = %d ]%s[ END ]\r\n\r\n", p->len, strbuf);

	parse_request(strbuf, p->len, &req);

	/* Find server entry from requested URL */
	for (i=0; resources[i].url != 0; i++){
		if (strncmp(resources[i].url, req.url, strlen(resources[i].url)) == 0) {
			break;
		}
	}


    memset(&res, 0, sizeof(response_t)) ;
	res.code = RES_OK;
	res.content = "Hello World!\r\n";
	if (resources[i].callback != 0){
		resources[i].callback(&req, &res);
	} else {
        xil_printf("URL not implemented: %s, redirecting...\r\n", req.url);
        res.code = RES_REDIRECT;
		strcpy(res.headers[0].name, "Location");
		strcpy(res.headers[0].value, "https://dl.dropboxusercontent.com/u/44070581/CoolLights/index.html");
        res.content = "https://dl.dropboxusercontent.com/u/44070581/CoolLights/index.html";
	}
	res.content_length = strlen(res.content);

	/* Set Response */
	send_response(tpcb, &res);

	tcp_close(tpcb);
	tcp_recv(tpcb, NULL);

	/* free the received pbuf */
	pbuf_free(p);

	return ERR_OK;
}

err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	static int connection = 1;

	/* set the receive callback for this connection */
	tcp_recv(newpcb, recv_callback);

	/* just use an integer number indicating the connection id as the
	   callback argument */
	tcp_arg(newpcb, (void*)connection);

	/* increment for subsequent accepted connections */
	connection++;

	return ERR_OK;
}


int http_server_start(uint16_t port)
{
	struct tcp_pcb *pcb;
	err_t err;

	/* create new TCP PCB structure */
	pcb = tcp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */
	err = tcp_bind(pcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	/* we do not need any arguments to callback functions */
	tcp_arg(pcb, NULL);

	/* listen for connections */
	pcb = tcp_listen(pcb);
	if (!pcb) {
		xil_printf("Out of memory while tcp_listen\n\r");
		return -3;
	}

	/* specify callback to use for incoming connections */
	tcp_accept(pcb, accept_callback);
	xil_printf("%s ... OK\r\n", __func__);

	return 0;
}
