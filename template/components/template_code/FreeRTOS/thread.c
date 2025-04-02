/**
 * @file app_main.c
 *
 * @brief Code example for FreeRTOS threads.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

/**
 * @brief This function prints out "world!".
 *
 * @param [in] p_parameter This is the parameter that is passed to the task.
 */
static void _some_task(void *p_parameter);

//------------------------- STATIC DATA & CONSTANTWS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void app_main(void)
{
    // ...

    xTaskCreate(&_some_task, "some_task", 2 * 1024, NULL, 5, NULL); /* All of these numbers should be MACROS or static const*/
    
    // for(;;) {}
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _some_task(void *p_parameter)
{
    for(;;)
    {
        // some work
    }
}

//---------------------------- INTERRUPT HANDLERS ------------------------------
