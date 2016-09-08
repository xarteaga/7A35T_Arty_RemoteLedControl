#ifndef SW_SYSTEM_SCHEDULER_H
#define SW_SYSTEM_SCHEDULER_H

/* Includes */
#include "xil_types.h"

/* Configuration parameters */
#define SCHEDULER_MAX_ENTRIES 16

/* Datatypes */
typedef void (*scheduler_callback) (u32 elapsed);

typedef struct {
    u32 timestamp;
    u32 period;
    scheduler_callback callback;
} scheduler_entry_t;

void scheduler_interrupt_handler();
void scheduler_add_entry(scheduler_entry_t *entry);
void scheduler_init();

#endif //SW_SYSTEM_SCHEDULER_H
