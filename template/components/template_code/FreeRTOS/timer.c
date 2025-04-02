/**
 * @file app_main.c
 *
 * @brief Code example for FreeRTOS timers.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include <stdio.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

/**
 * @brief This function is a callback for software timer, it toggles the LED.
 *
 * @param [in] p_timer Timer handle for the timer that invoked the callback.
 */
static void _led_timer_cb(TimerHandle_t p_timer);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static TimerHandle_t timer_hndl = NULL;

static const uint32_t timer_period_ms = 500u;
//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void app_main(void)
{
    // ...

    timer_hndl = xTimerCreate("led_timer", (timer_period_ms / portTICK_PERIOD_MS), pdTRUE, NULL, _some_timer_cb);

    xTimerStart(timer_hndl, 0);

    vTaskSuspend(NULL);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS ------------------------------

static void _some_timer_cb(TimerHandle_t p_timer)
{
    // ... some work

    // reset ako želimo da se task ponovi
    xTimerResetFromISR(timer_hndl, NULL);
}
