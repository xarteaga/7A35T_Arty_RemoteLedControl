
#ifndef SW_SYSTEM_FILE_LOADER_H
#define SW_SYSTEM_FILE_LOADER_H

#include "xil_types.h"

typedef enum {
    FILE_LOADER_TYPE_TEXT = 0,
    FILE_LOADER_TYPE_HTML,
    FILE_LOADER_TYPE_CSS,
    FILE_LOADER_TYPE_JAVASCRIPT
} file_loader_type_t;

typedef struct {
    file_loader_type_t type;
    const char *url;
    u32 size;
    char *content;
} file_loader_entry_t;

#endif //SW_SYSTEM_FILE_LOADER_H
