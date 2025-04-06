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
            }
        }
    }
}
