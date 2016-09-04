
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include "lwip/err.h"
#include "lwip/tcp.h"

#include "file_loader.h"

struct tcp_pcb *pcb;

file_loader_entry_t file_loader_entries [] = {
        {FILE_LOADER_TYPE_HTML, "xarteaga/7A35T_Arty_RemoteLedControl/master/html/index.html", 0, NULL},
        {FILE_LOADER_TYPE_TEXT, NULL, 0, NULL}
};

void file_loader_init() {

}

