/**
 * @file comms.c
 *
 * @brief This file is responsible for communication between tasks.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "comms.h"
#include <stdio.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------
EventGroupHandle_t xGuiButtonEventGroup;
QueueHandle_t xGuiUpdateQueue;

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void comms_init(void) {
    xGuiButtonEventGroup = xEventGroupCreate();
    if( xGuiButtonEventGroup == NULL )
    {
        printf("The xGuiButtonEventGroup was not created successfully\n");
        return;
    }

    xGuiUpdateQueue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(LabelData));
    if(xGuiUpdateQueue == NULL)
    {
        printf("The xGuiUpdateQueue queue was not initialized successfully\n");
        return;
    }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

