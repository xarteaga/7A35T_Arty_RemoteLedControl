//
// Created by vaxi on 4/09/16.
//

#include <string.h>

#include "web_loader.h"
#include "web_loader_data.h"
#include "../server/server.h"

void web_loader_init() {

}

void *web_loader_resource(request_t *req, response_t *res){
    res->code = RES_OK;
    strcpy(res->headers[0].name, "Content-Type");
    strcpy(res->headers[0].value, "text/html; charset=utf-8");
    res->content = web_loader_data;

    return NULL;
}