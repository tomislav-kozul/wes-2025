/**
 * @file font_sensor.c
 *
 * @brief Source file for front-sensor controll.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "ultrasonic.h"
#include "front_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "comms.h"

//---------------------------------- MACROS -----------------------------------
#define MAX_DISTANCE_CM 500 // 5m max

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

#define TRIGGER_GPIO 27
#define ECHO_GPIO 26


//------------------------- STATIC DATA & CONSTANTS ---------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief Task for reading input on front sensor of the car.
 *
 * @param [in] p_parameter This is the parameter that is passed to the task.
 */
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

    printf("Front sensor\n");
    xTaskCreate(&_read_front_sensor_task, "front_sensor_task", 2 * 1024, NULL, 5, NULL);
}



//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _read_front_sensor_task(void *p_parameter)
{
    (void)*p_parameter;
    for(;;)
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
        else {
            float distanceCM = distance * 100;
            if (distanceCM < 40) {
                xEventGroupSetBits(
                    xGuiButtonEventGroup, 
                    FRONT_SENSOR_ZONE_RED);
            } else if (distanceCM < 70) {
                xEventGroupSetBits(
                    xGuiButtonEventGroup, 
                    FRONT_SENSOR_ZONE_YELLOW);
            } else if (distanceCM < 100) {
                xEventGroupSetBits(
                    xGuiButtonEventGroup, 
                    FRONT_SENSOR_ZONE_GREEN);
            } else {
                xEventGroupSetBits(
                    xGuiButtonEventGroup, 
                    FRONT_SENSOR_ZONE_NONE);
            }

        }
            //printf("Distance: %0.04f cm\n", distance*100);

            // red zone         < 40
            // yellow zone      < 80
            // green zone       < 100
            
            
            //if distance_cm <= 80:

            //if distance_cm <= 40:

        vTaskDelay(pdMS_TO_TICKS(500));

    }
}

//---------------------------- INTERRUPT HANDLERS ------------------------------