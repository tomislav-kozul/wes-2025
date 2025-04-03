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

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void comms_init(void) {
    xGuiButtonEventGroup = xEventGroupCreate();
    if( xGuiButtonEventGroup == NULL )
    {
        printf("The xGuiButtonEventGroup was not created successfully\n");
        return;
    }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

