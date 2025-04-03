/**
 * @file app_main.c
 *
 * @brief First code example for ESP32.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

//----------------------------- CUSTOM INCLUDES -------------------------------

//#include "gpio_led.h"
//#include "gpio_button.h"
//#include "gui/gui.h"
#include "user_interface/user_interface.h"

//----------------------------------- PINS ------------------------------------
#define GPIO_LED_RED (26U)
#define GPIO_LED_GREEN (27U)
#define GPIO_LED_BLUE (14U)

#define GPIO_BUTTON_1 (36U)
#define GPIO_BUTTON_2 (32U)
#define GPIO_BUTTON_3 (33U)
#define GPIO_BUTTON_4 (25U)

#define GPIO_JOY_X (34U)
#define GPIO_JOY_Y (35U)

#define GPIO_UART_RX (3U)
#define GPIO_UART_TX (1U)

#define GPIO_I2C_SCL (21U)
#define GPIO_I2C_SDA (22U)


//--------------------------------- COMPONENTS --------------------------------

//---------------------------------- MACROS -----------------------------------
#define DELAY_TIME_MS (1000U)
#define DELAY_TIME_MS_DEBOUNCE (50U)

#define GPIO_BIT_MASK(X) ((1ULL << (X)))

#define TASK_STACK_SIZE     (2048U) // default veličina stoga za task
#define TASK_PRIORITY_1     (1U)
#define TASK_PRIORITY_2     (2U)
#define TASK_PRIORITY_3     (3U)
#define TASK_PRIORITY_4     (4U)
#define TASK_PRIORITY_5     (5U)

#define QUEUE_LENGTH        (10U) // default veličina reda poruka

#define ESP_WIFI_SSID       (" ")
#define ESP_WIFI_PASS       (" ")
#define ESP_WIFI_CHANNEL    (1U)
#define MAX_STA_CONN        (4U)

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------

void app_main(void)
{

    /*for(;;)
    {
        led_on(GPIO_LED_RED);
        vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);

        led_off(GPIO_LED_RED);
        vTaskDelay(DELAY_TIME_MS / portTICK_PERIOD_MS);

        printf("Button 1 pressed: %lu times.\n", button1_press_count);
    }*/
    user_interface_init();
}
