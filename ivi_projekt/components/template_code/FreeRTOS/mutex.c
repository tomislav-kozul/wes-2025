/**
 * @file app_main.c
 *
 * @brief Code example for FreeRTOS MUTEX.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

//---------------------------------- MACROS -----------------------------------
#define TASK_STACK_SIZE            (2048U)
#define TASK_PRIORITY              (5U)

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

/**
 * @brief Task that increments a shared counter with mutex protection.
 *
 * This task acquires a mutex to safely increment a shared variable and logs the value.
 *
 * @param[in] p_param Unused task parameter.
 */
static void _task_a(void *p_param);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static SemaphoreHandle_t mutex_handle = NULL;
static uint32_t s_shared_counter = 0;           // primjer varijable u kriticnoj sekciji
static const char *TAG = "mutex_example";

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void app_main(void)
{
    // ...

    mutex_handle = xSemaphoreCreateMutex();
    if (NULL == mutex_handle)
    {
        ESP_LOGE(TAG, "Failed to create mutex");
        return;
    }

    xTaskCreate(&_task_a, "Task_A", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // for (;;) { }
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

static void _task_a(void *p_param)
{
    (void)p_param;

    for (;;)
    {
        if (pdTRUE == xSemaphoreTake(mutex_handle, portMAX_DELAY))
        {
            // critical section
            xSemaphoreGive(mutex_handle);
        }

        // delay
    }
}
