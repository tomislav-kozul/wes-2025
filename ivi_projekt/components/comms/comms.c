#include "comms.h"
#include <stdio.h>

QueueHandle_t xAppEventQueue;

void comms_init(void) {
    xAppEventQueue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(AppEvent));
    if (xAppEventQueue == NULL) {
        printf("The xAppEventQueue queue was not initialized successfully\n");
        return;
    }
}
