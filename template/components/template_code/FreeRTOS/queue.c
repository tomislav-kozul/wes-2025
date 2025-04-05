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
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

//---------------------------------- MACROS -----------------------------------

#define MAIN_TASK_DELAY_MS         (2000U)
#define TASK_DELAY_MS              (1000U)

#define TASK_STACK_SIZE            (2048U)
#define TASK_PRIORITY              (5U)

#define QUEUE_LENGTH               (10U)

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

/**
 * @brief Producer task that sends values into a FreeRTOS queue.
 *
 * This task periodically sends incrementing values into a shared queue for consumption
 * by another task.
 *
 * @param[in] p_param Unused task parameter.
 */
static void _task_producer(void *p_param);

/**
 * @brief Consumer task that receives values from a FreeRTOS queue.
 *
 * This task blocks on the queue until it receives a value, then logs it.
 *
 * @param[in] p_param Unused task parameter.
 */
static void _task_consumer(void *p_param);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static QueueHandle_t s_queue_handle = NULL;
static const char *TAG = "queue_example";

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void app_main(void)
{
    s_queue_handle = xQueueCreate(QUEUE_LENGTH, sizeof(uint32_t));
    if (NULL == s_queue_handle)
    {
        ESP_LOGE(TAG, "Failed to create queue");
        return;
    }

    xTaskCreate(&_task_producer, "Task_Producer", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(&_task_consumer, "Task_Consumer", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    return;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

static void _task_producer(void *p_param)
{
    (void)p_param;

    uint32_t count = 0;

    for (;;)
    {
        if (pdTRUE == xQueueSend(s_queue_handle, &count, portMAX_DELAY))
        {
            ESP_LOGI(TAG, "[Producer] Sent value: %lu", count);
            count++;
        }

        // vTaskDelay(TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

static void _task_consumer(void *p_param)
{
    (void)p_param;

    uint32_t received_value = 0;

    for (;;)
    {
        if (pdTRUE == xQueueReceive(s_queue_handle, &received_value, portMAX_DELAY))
        {
            ESP_LOGI(TAG, "[Consumer] Received value: %lu", received_value);
        }

        // vTaskDelay(TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

