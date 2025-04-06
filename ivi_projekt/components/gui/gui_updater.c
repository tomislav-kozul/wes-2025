#include "comms.h"
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

    for (;;)
    {
        // Wait for data from the queue
        if (xQueueReceive(xGuiUpdateQueue, &receivedData, portMAX_DELAY)) {
            /* Try to take the semaphore, call lvgl related function on success */
            if(pdTRUE == xSemaphoreTake(p_gui_semaphore, portMAX_DELAY))
            {
                lv_label_set_text_fmt(receivedData.label, "%d", receivedData.data);
                xSemaphoreGive(p_gui_semaphore);
    for (;;) {
        if (xQueueReceive(xAppEventQueue, &event, 100 / portTICK_PERIOD_MS)) {
            switch (event.type) {
                case EVENT_UPDATE_LABEL:
                    if (pdTRUE == xSemaphoreTake(p_gui_semaphore, portMAX_DELAY)) {
                        lv_label_set_text(event.data.update_label.label, event.data.update_label.text);
                        xSemaphoreGive(p_gui_semaphore);
                    }
                    break;

                case EVENT_FRONT_SENSOR_GREEN:
                case EVENT_FRONT_SENSOR_YELLOW:
                case EVENT_FRONT_SENSOR_RED:
                case EVENT_FRONT_SENSOR_NONE:
                    if (pdTRUE == xSemaphoreTake(p_gui_semaphore, portMAX_DELAY)) {
                        lv_obj_set_style_bg_opa(event.data.sensor_alpha.container_red, event.data.sensor_alpha.data_red, LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_opa(event.data.sensor_alpha.container_yellow, event.data.sensor_alpha.data_yellow, LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_opa(event.data.sensor_alpha.container_green, event.data.sensor_alpha.data_green, LV_PART_MAIN | LV_STATE_DEFAULT);
                        xSemaphoreGive(p_gui_semaphore);
                    }
                    break;

                default:
                    // Ignore unrelated events
                    break;

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
    }
}
