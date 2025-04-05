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
EventGroupHandle_t xGpioButtonEventGroup;
QueueHandle_t xGuiUpdateQueue;
QueueHandle_t xTempReadingQueue;
QueueHandle_t xTempSetQueue;
QueueHandle_t xFrontSensorQueue;

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void comms_init(void) {
    xGuiButtonEventGroup = xEventGroupCreate();
    if( xGuiButtonEventGroup == NULL )
    {
        printf("The xGuiButtonEventGroup was not created successfully\n");
        return;
    }

    xGpioButtonEventGroup = xEventGroupCreate();
    if( xGpioButtonEventGroup == NULL )
    {
        printf("The xGpioButtonEventGroup was not created successfully\n");
        return;
    }

    xGuiUpdateQueue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(GuiMessage));
    if(xGuiUpdateQueue == NULL)
    {
        printf("The xGuiUpdateQueue queue was not initialized successfully\n");
        return;
    }

    xTempReadingQueue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(float));
    if(xTempReadingQueue == NULL)
    {
        printf("The xTempReadingQueue queue was not initialized successfully\n");
        return;
    }

    xTempSetQueue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(int));
    if(xTempSetQueue == NULL)
    {
        printf("The xTempSetQueue queue was not initialized successfully\n");
        return;
    }

    xFrontSensorQueue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(sensorAlphaUpdate));
    if(xFrontSensorQueue == NULL)
    {
        printf("The xFrontSensorQueue queue was not initialized successfully\n");
        return;
    }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------