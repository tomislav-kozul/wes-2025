#include "comms.h"
#include "ui_helpers.h"
#include "gui.h"
#include <stdio.h>

static TaskHandle_t p_gui_updater_task = NULL;

static void _gui_updater_task(void *p_parameter);

void gui_updater_init(void)
{
    xTaskCreate(_gui_updater_task, "gui_updater", 4096 * 2, NULL, 5, &p_gui_updater_task);
}

static void _gui_updater_task(void *p_parameter)
{
    AppEvent event;
    AppEvent eventToRemove;
    LabelData receivedData;
    char labelText[64];


    for (;;) {
        if (xQueuePeek(xAppEventQueue, &event, 100 / portTICK_PERIOD_MS)) {
            switch (event.type) {
                case EVENT_UPDATE_LABEL:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    if (pdTRUE == xSemaphoreTake(p_gui_semaphore, portMAX_DELAY)) {
                        lv_label_set_text(event.data.update_label.label, event.data.update_label.text);
                        xSemaphoreGive(p_gui_semaphore);
                    }
                    break;

                case EVENT_FRONT_SENSOR_GREEN:
                case EVENT_FRONT_SENSOR_YELLOW:
                case EVENT_FRONT_SENSOR_RED:
                case EVENT_FRONT_SENSOR_NONE:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    if (pdTRUE == xSemaphoreTake(p_gui_semaphore, portMAX_DELAY)) {
                        lv_obj_set_style_bg_opa(event.data.sensor_alpha.container_red, event.data.sensor_alpha.data_red, LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_opa(event.data.sensor_alpha.container_yellow, event.data.sensor_alpha.data_yellow, LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_opa(event.data.sensor_alpha.container_green, event.data.sensor_alpha.data_green, LV_PART_MAIN | LV_STATE_DEFAULT);
                        xSemaphoreGive(p_gui_semaphore);
                    }
                    break;

                case EVENT_AC_TEMP_UPDATE:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    if (pdTRUE == xSemaphoreTake(p_gui_semaphore, portMAX_DELAY)) {
                        snprintf(labelText, sizeof(labelText), "%d \u00b0C", event.data.temp_set.temperature);
                        lv_label_set_text(ui_SetTemperatureLabel, labelText);
                        xSemaphoreGive(p_gui_semaphore);
                    }
                    break;

                case EVENT_AMBIENT_TEMP_UPDATE:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    if (pdTRUE == xSemaphoreTake(p_gui_semaphore, portMAX_DELAY)) {
                        snprintf(labelText, sizeof(labelText), "%2.1f \u00b0C", event.data.temp_reading.temperature);
                        lv_label_set_text(ui_temperatureLabelAC, labelText);
                        xSemaphoreGive(p_gui_semaphore);
                    }
                    break;

                default:
                    // Ignore unrelated events
                    break;
            }
        }

        if (xQueueReceive(xGuiUpdateQueue, &receivedData, 100 / portTICK_PERIOD_MS))
        {
            if (pdTRUE == xSemaphoreTake(p_gui_semaphore, portMAX_DELAY))
            {
                switch (receivedData.label_type)
                {
                    case LABEL_TYPE_TEXT:
                        lv_label_set_text(receivedData.label, receivedData.content.text);
                        break;
        
                    case LABEL_TYPE_INT:
                        lv_label_set_text_fmt(receivedData.label, "%d", receivedData.content.value);
                        break;
        
                    default:
                        // Optional: handle unknown types
                        break;
                }
                xSemaphoreGive(p_gui_semaphore);
            }
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
