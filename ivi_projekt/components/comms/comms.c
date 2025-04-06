#include "comms.h"
#include <stdio.h>

QueueHandle_t xAppEventQueue;
QueueHandle_t xGuiUpdateQueue;

void comms_init(void) {
    xAppEventQueue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(AppEvent));
    if (xAppEventQueue == NULL) {
        printf("The xAppEventQueue queue was not initialized successfully\n");
        return;
    }

    xGuiUpdateQueue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(LabelData));
    if (xGuiUpdateQueue == NULL) {
        printf("The xGuiUpdateQueue queue was not initialized successfully\n");
        return;
    }
}
