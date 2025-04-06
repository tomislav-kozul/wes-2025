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
#include "gui.h"
#include "user_interface.h"
#include "comms.h"
#include "temperature_sensor.h"
#include "wifi_manager.h"

//----------------------------------- PINS ------------------------------------

//--------------------------------- COMPONENTS --------------------------------

//---------------------------------- MACROS -----------------------------------
#define DELAY_TIME_MS (1000U)
#define DELAY_TIME_MS_DEBOUNCE (50U)

#define TASK_STACK_SIZE     (2048U) // default veličina stoga za task
#define TASK_PRIORITY_1     (1U)
#define TASK_PRIORITY_2     (2U)
#define TASK_PRIORITY_3     (3U)
#define TASK_PRIORITY_4     (4U)
#define TASK_PRIORITY_5     (5U)

#define QUEUE_LENGTH        (10U) // default veličina reda poruka

#define ESP_WIFI_SSID       ("S24")
#define ESP_WIFI_PASS       ("pass1234!")
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
    comms_init();
    user_interface_init();
    temp_sensor_task_init();
    wifi_manager_init_sta();
    wifi_manager_connect(ESP_WIFI_SSID, ESP_WIFI_PASS);
    
}
