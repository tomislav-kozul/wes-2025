/**
 * @file front_sensor.c
 *
 * @brief Source file for front-sensor control.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "ultrasonic.h"
#include "front_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ui_helpers.h"
#include "comms.h"

//---------------------------------- MACROS -----------------------------------
#define MAX_DISTANCE_CM 500 // 5m max

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

#define TRIGGER_GPIO 27
#define ECHO_GPIO 26

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
static void _read_front_sensor_task(void *p_parameter);

//------------------------------- GLOBAL DATA ---------------------------------
ultrasonic_sensor_t sensor = {
    .trigger_pin = TRIGGER_GPIO,
    .echo_pin = ECHO_GPIO
};

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void front_sensor_init(void)
{
    ultrasonic_init(&sensor);
    xTaskCreate(&_read_front_sensor_task, "front_sensor_task", 2 * 1024, NULL, 5, NULL);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _read_front_sensor_task(void *p_parameter)
{
    (void)*p_parameter;
    for (;;)
    {
        float distance;
        esp_err_t res = ultrasonic_measure(&sensor, MAX_DISTANCE_CM, &distance);
        if (res != ESP_OK)
        {
            printf("Error %d: ", res);
            switch (res)
            {
                case ESP_ERR_ULTRASONIC_PING:
                    printf("Cannot ping (device is in invalid state)\n");
                    break;
                case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
                    printf("Ping timeout (no device found)\n");
                    break;
                case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
                    printf("Echo timeout (i.e. distance too big)\n");
                    break;
                default:
                    printf("%s\n", esp_err_to_name(res));
            }
        }
        else
        {
            float distanceCM = distance * 100;
            AppEvent sensor_event;
        
            if (distanceCM < 40)
                sensor_event.type = EVENT_FRONT_SENSOR_RED;
            else if (distanceCM < 70)
                sensor_event.type = EVENT_FRONT_SENSOR_YELLOW;
            else if (distanceCM < 100)
                sensor_event.type = EVENT_FRONT_SENSOR_GREEN;
            else
                sensor_event.type = EVENT_FRONT_SENSOR_NONE;
        
            uint8_t red_alpha = 50, yellow_alpha = 50, green_alpha = 50;
        
            switch (sensor_event.type) {
                case EVENT_FRONT_SENSOR_RED:
                    red_alpha = 255;
                    yellow_alpha = 255;
                    green_alpha = 255;
                    break;
                case EVENT_FRONT_SENSOR_YELLOW:
                    yellow_alpha = 255;
                    green_alpha = 255;
                    break;
                case EVENT_FRONT_SENSOR_GREEN:
                    green_alpha = 255;
                    break;
                default:
                    // All remain at 50
                    break;
            }
        
            sensor_event.data.sensor_alpha = (typeof(sensor_event.data.sensor_alpha)) {
                .container_red = ui_frontSensorRedZone,
                .container_yellow = ui_frontSensorYellowZone,
                .container_green = ui_frontSensorGreenZone,
                .data_red = red_alpha,
                .data_yellow = yellow_alpha,
                .data_green = green_alpha
            };
        
            xQueueSend(xAppEventQueue, &sensor_event, portMAX_DELAY);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
