#include "user_interface.h"
#include "gpio_led.h"
#include "gui.h"
#include "ui_helpers.h"
#include "gui_updater.h"
#include "comms.h"
#include "pins.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "front_sensor.h"
#include <stdio.h>
#include "freertos/timers.h"

#include "stdio.h"
#include "time.h"
#include "sys/time.h"

#define INIT_DELAY 2000

static TaskHandle_t p_user_interface_task = NULL;

static void _user_interface_task(void *p_parameter);
static void vTimeUpdateCallback(TimerHandle_t xTimer);
//static void _time_display_task(void *p_parameter);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static TimerHandle_t timeUpdateTimer = NULL;
static bool isFirstExecution = true;
//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void user_interface_init(void)
{
    led_toggle_state_init();
    led_init(GPIO_LED_BLUE);
    gui_init();
    gui_updater_init();
    
    vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);

    front_sensor_init();

    if (pdPASS != xTaskCreate(&_user_interface_task, "user_interface_task", 2 * 1024, NULL, 5, &p_user_interface_task)) {
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

static void _user_interface_task(void *p_parameter)
{
    AppEvent event;
    AppEvent eventToRemove;

    for (;;) {
        if (xQueuePeek(xAppEventQueue, &event, 80 / portTICK_PERIOD_MS)) {
            switch (event.type) {
                case EVENT_AC_ON_OFF:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    AppEvent hvac_msg = {
                        .type = HVAC_AC_ON_OFF,
                        .data = {},
                    };
                    xQueueSend(xAppEventQueue, &hvac_msg, portMAX_DELAY);
                    break;
                case EVENT_FRONT_SENSOR_GREEN:
                case EVENT_FRONT_SENSOR_YELLOW:
                case EVENT_FRONT_SENSOR_RED:
                case EVENT_FRONT_SENSOR_NONE:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    xQueueSend(xAppEventQueue, &event, portMAX_DELAY); // Forward to GUI updater
                    break;

                case EVENT_TEMP_READING:
                {
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    AppEvent gui_msg = {
                        .type = EVENT_AMBIENT_TEMP_UPDATE,
                        .data.temp_reading = {
                            .temperature = event.data.temp_reading.temperature
                        }
                    };
                    xQueueSend(xAppEventQueue, &gui_msg, portMAX_DELAY);
                    AppEvent hvac_msg = {
                        .type = HVAC_AMBIENT_TEMP_UPDATE,
                        .data.temp_reading = {
                            .temperature = event.data.temp_reading.temperature
                        }
                    };
                    xQueueSend(xAppEventQueue, &hvac_msg, portMAX_DELAY);
                    break;
                }

                case EVENT_AC_TEMP_SET:
                {
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    AppEvent gui_msg = {
                        .type = EVENT_AC_TEMP_UPDATE,
                        .data.temp_set = {
                            .temperature = event.data.temp_set.temperature
                        }
                    };
                    xQueueSend(xAppEventQueue, &gui_msg, portMAX_DELAY);
                    AppEvent hvac_msg = {
                        .type = HVAC_AC_TEMP_UPDATE,
                        .data.temp_set = {
                            .temperature = event.data.temp_set.temperature
                        }
                    };
                    xQueueSend(xAppEventQueue, &hvac_msg, portMAX_DELAY);
                    break;
                }

                default:
                    // printf("Unknown event type: %d\n", event.type);
                    break;
            }
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

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
    xQueueSend(xGuiUpdateQueue, &timeLabel, portMAX_DELAY);
    timeLabel.label = ui_currentTimePark;
    xQueueSend(xGuiUpdateQueue, &timeLabel, portMAX_DELAY);
    timeLabel.label = ui_currentTimeRadio;
    xQueueSend(xGuiUpdateQueue, &timeLabel, portMAX_DELAY);
    timeLabel.label = ui_currentTimeHVAC;
    xQueueSend(xGuiUpdateQueue, &timeLabel, portMAX_DELAY);
    timeLabel.label = ui_currentTimeAC;
    xQueueSend(xGuiUpdateQueue, &timeLabel, portMAX_DELAY);

    LabelData dateLabel = {
        .label = ui_currentDateHome,
        .label_type = LABEL_TYPE_TEXT
    };
    snprintf(dateLabel.content.text, sizeof(dateLabel.content.text), "%s", date_str);
    xQueueSend(xGuiUpdateQueue, &dateLabel, portMAX_DELAY);
    dateLabel.label = ui_currentDatePark;
    xQueueSend(xGuiUpdateQueue, &dateLabel, portMAX_DELAY);
    dateLabel.label = ui_currentDateRadio;
    xQueueSend(xGuiUpdateQueue, &dateLabel, portMAX_DELAY);
    dateLabel.label = ui_currentDateHVAC;
    xQueueSend(xGuiUpdateQueue, &dateLabel, portMAX_DELAY);
    dateLabel.label = ui_currentDateAC;
    xQueueSend(xGuiUpdateQueue, &dateLabel, portMAX_DELAY);
}

