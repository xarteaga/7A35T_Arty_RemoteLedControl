
/* Standard C Includes */
#include <string.h>
#include <stdio.h>

/* Xilinx Includes */
#include <xbasic_types.h>

/* Project Includes */
#include "scheduler.h"

/* Variables */
static u32 timestamp = 0;
scheduler_entry_t *scheduler_entries [SCHEDULER_MAX_ENTRIES];
u32 scheduler_entries_count;
Xboolean scheduler_busy = TRUE;

void scheduler_interrupt_handler(){
    u32 i = 0, elapsed = 0;

    /* Check if it is busy */
    if (scheduler_busy == FALSE) {
        /* Rise Busy */
        scheduler_busy = TRUE;

        /* For each entry */
        for (i = 0; i < scheduler_entries_count; i++) {
            /* Get entry */
            scheduler_entry_t *entry = scheduler_entries[i];

            /* Process */
            elapsed = (u32)(timestamp - entry->timestamp);
            if (elapsed >= entry->period) {
                /* Call callback if required */
                entry->callback((u32)elapsed);

                /* Update timestamp */
                entry->timestamp = timestamp;
            }
        }

        /* Down Busy */
        scheduler_busy = FALSE;
    }

    /* Increase timestamp */
    timestamp++;
}

void scheduler_init(){
    /* Set all entries to zero */
    memset(scheduler_entries, 0, sizeof(scheduler_entries));

    /* Set entry count to zero */
    scheduler_entries_count = 0;

    /* Reset Timestamp */
    timestamp = 0;

    /* Reset busy */
    scheduler_busy = FALSE;

    xil_printf("%s ... OK\r\n", __func__);
}

void scheduler_add_entry(scheduler_entry_t *entry) {
    /* Check that the list has not reached its limit */
    if (scheduler_entries_count < SCHEDULER_MAX_ENTRIES) {
        /* Set new entry */
        scheduler_entries[scheduler_entries_count] = entry;

        /* Increment number of entries */
        scheduler_entries_count++;
    } else {
        xil_printf("%s: List has reached its limit.\r\n", __FUNCTION__);
    }
}
