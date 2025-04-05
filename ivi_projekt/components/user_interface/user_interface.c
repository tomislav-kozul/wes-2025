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
#include "gui.h"
#include "ui_helpers.h"
#include "gui_updater.h"
#include "comms.h"
#include "pins.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

#include "stdio.h"
#include "time.h"
#include "sys/time.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief User inteface task.
 *
 * @param [in] p_parameter This is the parameter that is passed to the task.
 */
static void _user_interface_task(void *p_parameter);
static void vTimeUpdateCallback(TimerHandle_t xTimer);
//static void _time_display_task(void *p_parameter);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static TaskHandle_t p_user_interface_task = NULL;
static TimerHandle_t timeUpdateTimer = NULL;
static bool isFirstExecution = true;
//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void user_interface_init(void)
{
    led_toggle_state_init();
    led_init(GPIO_LED_BLUE);
    led_init(GPIO_LED_GREEN);
    button1_init();
    button2_init();
    button3_init();
    button4_init();
    gui_init();
    gui_updater_init();
    
    // izrada taska koji provjerava red poruka
    if (pdPASS != xTaskCreate(&_user_interface_task, "user_interface_task", 2 * 1024, NULL, 5, &p_user_interface_task))
    {
        printf("User interface task was not initialized successfully\n");
        return;
    }

    // timezone to Central European (adjust as needed)
    setenv("TZ", "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00", 1);
    tzset();

    timeUpdateTimer = xTimerCreate(
    "TimeUpdateTimer",            // Timer name
    pdMS_TO_TICKS(1000),          // Timer period in ticks (1 second at first, then change to 60s in timer
    pdTRUE,                       // Auto-reload set to true
    (void *)0,                    // Timer ID
    vTimeUpdateCallback           // Callback function
    );

    // Check if timer was created successfully
    if (timeUpdateTimer == NULL)
    {
        printf("Timer not created\n");
    }
    else
    {
        if (xTimerStart(timeUpdateTimer, 0) == pdPASS)
        {
            printf("Timer started successfully!\n");
        }
        else
        {
            printf("Failed to start timer\n");
        }
    }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _user_interface_task(void *p_parameter)
{
    EventBits_t uxBits;
    int labelValue = 0;

    for (;;)
    {
        // Blockingly wait on an event.
        if ((xGuiButtonEventGroup != NULL) && (uxBits = xEventGroupWaitBits(xGuiButtonEventGroup, 
                GUI_APP_EVENT_BUTTON_JEBENI_PRESSED 
                | GPIO_BUTTON_1_PRESS
                | GPIO_BUTTON_2_PRESS
                | GPIO_BUTTON_3_PRESS
                | GPIO_BUTTON_4_PRESS
                | WIFI_CONNECTED_BIT, 
            pdTRUE, pdFALSE, portMAX_DELAY)))
        {
            printf("GUI event received %ld\n", uxBits);

            // TODO: Probably should check the flags with "&" and "==" operators in case multiple flags are set
            switch (uxBits)
            {
            case GUI_APP_EVENT_BUTTON_JEBENI_PRESSED:
                led_toggle(GPIO_LED_BLUE);
                labelValue++;
                LabelData labelData = {
                    .label = ui_ButtonPressCounter,
                    .label_type = LABEL_TYPE_INT,
                    .content.value = labelValue
                };
                xQueueSend(xGuiUpdateQueue, &labelData, portMAX_DELAY);
                break;
            case GPIO_BUTTON_1_PRESS:
                printf("1 - %lu\n", button_press_count[0]);
                break;
            case GPIO_BUTTON_2_PRESS:
                printf("2 - %lu\n", button_press_count[1]);
                break;
            case GPIO_BUTTON_3_PRESS:
                printf("3 - %lu\n", button_press_count[2]);
                break;
            case GPIO_BUTTON_4_PRESS:
                printf("4 - %lu\n", button_press_count[3]);
                break;
            case WIFI_CONNECTED_BIT:
                printf("WiFi connected!");
                //update label
                break;
            default:
                printf("Uknown GUI event\n");
                break;
            }
        }
    }
}


/*static void _time_display_task(void *p_parameter)
{
    struct tm timeinfo;
    int last_minute = -1;

    char time_str[16];
    char date_str[16];

    while (1)
    {
        time_t now = time(NULL);
        localtime_r(&now, &timeinfo);
        printf("Task dode");
        if (timeinfo.tm_min != last_minute)
        {
            last_minute = timeinfo.tm_min;

            // Format time and date (e.g. "14:05", "2024-04-08")
            strftime(time_str, sizeof(time_str), "%H:%M", &timeinfo);
            strftime(date_str, sizeof(date_str), "%Y-%m-%d", &timeinfo);

            // Send time label
            LabelData timeLabel = {
                .label = ui_currentTimeHome,
                .label_type = LABEL_TYPE_TEXT
            };
            snprintf(timeLabel.content.text, sizeof(timeLabel.content.text), "%s", time_str);
            xQueueSend(xGuiUpdateQueue, &timeLabel, portMAX_DELAY);

            // Send date label
            LabelData dateLabel = {
                .label = ui_currentDateHome,
                .label_type = LABEL_TYPE_TEXT
            };
            snprintf(dateLabel.content.text, sizeof(dateLabel.content.text), "%s", date_str);
            xQueueSend(xGuiUpdateQueue, &dateLabel, portMAX_DELAY);
        }

        //int delay_ms = (60 - timeinfo.tm_sec) * 1000;
        vTaskDelay(pdMS_TO_TICKS(1000)); //delay for just how long it is until the next minute
    }
}*/


//---------------------------- INTERRUPT HANDLERS -----------------------------

static void vTimeUpdateCallback(TimerHandle_t xTimer)
{

    //change timer interrupt time
    if(isFirstExecution){
        xTimerChangePeriod(xTimer, pdMS_TO_TICKS(60000), 100 == pdPASS);
        isFirstExecution = false;
    }
    // Obtain the current time
    time_t now;
    struct tm timeinfo;
    char time_str[16];
    char date_str[16];

    time(&now);
    localtime_r(&now, &timeinfo);

    // Format the time and date strings
    strftime(time_str, sizeof(time_str), "%H:%M", &timeinfo);
    strftime(date_str, sizeof(date_str), "%Y-%m-%d", &timeinfo);

    // Create LabelData structures for time and date
    LabelData timeLabel = {
        .label = ui_currentTimeHome,
        .label_type = LABEL_TYPE_TEXT
    };
    snprintf(timeLabel.content.text, sizeof(timeLabel.content.text), "%s", time_str);

    LabelData dateLabel = {
        .label = ui_currentDateHome,
        .label_type = LABEL_TYPE_TEXT
    };
    snprintf(dateLabel.content.text, sizeof(dateLabel.content.text), "%s", date_str);

    // Send the updated labels to the GUI update queue
    xQueueSend(xGuiUpdateQueue, &timeLabel, portMAX_DELAY);
    xQueueSend(xGuiUpdateQueue, &dateLabel, portMAX_DELAY);
}

