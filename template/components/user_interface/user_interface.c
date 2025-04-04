/**
 * @file user_interface.c
 *
 * @brief This file is responsible for complete user interface (LEDs, buttons
 * and GUI).
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "user_interface.h"
#include "gpio_led.h"
#include "gpio_button.h"
#include "comms.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <stdio.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief User inteface task.
 *
 * @param [in] p_parameter This is the parameter that is passed to the task.
 */
static void _user_interface_task(void *p_parameter);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static TaskHandle_t p_user_interface_task = NULL;

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void user_interface_init(void)
{
    led_init(GPIO_LED_BLUE);
    button1_init();

    // izrada taska koji provjerava red poruka
    if (pdPASS != xTaskCreate(&_user_interface_task, "user_interface_task", 2 * 1024, NULL, 5, &p_user_interface_task))
    {
        printf("User interface task was not initialized successfully\n");
        return;
    }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _user_interface_task(void *p_parameter)
{
    EventBits_t uxBits;
    
    for (;;)
    {
        // Blockingly wait on an event.
        if ((xGuiButtonEventGroup != NULL) && (uxBits = xEventGroupWaitBits(xGuiButtonEventGroup, GUI_APP_EVENT_BUTTON_JEBENI_PRESSED, pdTRUE, pdFALSE, portMAX_DELAY)))
        {
            printf("GUI event received %ld\n", uxBits);

            // TODO: Probably should check the flags with "&" and "==" operators in case multiple flags are set
            switch (uxBits)
            {
            case GUI_APP_EVENT_BUTTON_JEBENI_PRESSED:
                led_on(GPIO_LED_BLUE);
                break;
            default:
                printf("Uknown GUI event\n");
                break;
            }
        }
    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------
