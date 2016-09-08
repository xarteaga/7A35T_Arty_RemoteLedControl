//
// Created by vaxi on 4/09/16.
//

#include <string.h>

#include "web_loader.h"
#include "web_loader_data.h"

static resource_t web_loader_res = { "/", (callback_t*) web_loader_resource };


void web_loader_init() {
    /* Add resources */
    server_add_resource(&web_loader_res);
}

void *web_loader_resource(request_t *req, response_t *res){
    res->code = RES_OK;
    strcpy(res->headers[0].name, "Content-Type");
    strcpy(res->headers[0].value, "text/html; charset=utf-8");
    res->content = (char *)web_loader_data;

    return NULL;
}