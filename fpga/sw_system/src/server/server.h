#ifndef _SERVER_H_
#define _SERVER_H_

#include "xil_types.h"

#define MAX_PARAMS 16
#define MAX_HEADERS 16

/* REQUEST METHODS */
#define REQ_GET 0
#define REQ_POST 1

/* RESPONSE CODES */
#define RES_OK 200
#define RES_REDIRECT 301
#define RES_BAD_REQUEST 400

typedef struct {
	char name[256];
	char value[256];
} param_t;

typedef struct {
	char name[256];
	char value[256];
} header_t;

typedef struct {
	u32 code;
	char url [256];
	param_t params[MAX_PARAMS];
	header_t headers[MAX_PARAMS];
} request_t;

typedef struct {
	u32 code;
	header_t headers[MAX_PARAMS];
	char *content;
	uint16_t content_length;
} response_t;

typedef void (*callback_t) (request_t *, response_t *);

typedef struct {
	const char *url;
    callback_t *callback;
} resource_t;

int http_server_start(uint16_t port);

#endif // _SERVER_H_
