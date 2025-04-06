#include "user_interface.h"
#include "gpio_led.h"
#include "gui.h"
#include "ui_helpers.h"
#include "gui_updater.h"
#include "speaker.h"
#include "comms.h"
#include "pins.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "front_sensor.h"
#include <stdio.h>

#define INIT_DELAY 2000

static TaskHandle_t p_user_interface_task = NULL;

static void _user_interface_task(void *p_parameter);

void user_interface_init(void)
{
    led_toggle_state_init();
    led_init(GPIO_LED_BLUE);
    gui_init();
    gui_updater_init();

    vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);

    front_sensor_init();
    init_speaker();

    if (pdPASS != xTaskCreate(&_user_interface_task, "user_interface_task", 2 * 1024, NULL, 5, &p_user_interface_task)) {
        printf("User interface task was not initialized successfully\n");
        return;
    }
}

static void _user_interface_task(void *p_parameter)
{
    AppEvent event;
    int labelValue = 0;

    for (;;) {
        if (xQueueReceive(xAppEventQueue, &event, 80 / portTICK_PERIOD_MS)) {
            switch (event.type) {
                case EVENT_GUI_BUTTON_PRESSED:
                    led_toggle(GPIO_LED_BLUE);
                    labelValue++;
                    break;
                case EVENT_AC_ON_OFF:
                    printf("AC_ON_OFF\n");
                    break;

                case EVENT_FRONT_SENSOR_GREEN:
                case EVENT_FRONT_SENSOR_YELLOW:
                case EVENT_FRONT_SENSOR_RED:
                case EVENT_FRONT_SENSOR_NONE:
                    xQueueSend(xAppEventQueue, &event, portMAX_DELAY); // Forward to GUI updater
                    break;

                case EVENT_TEMP_READING:
                {
                    AppEvent gui_msg = {
                        .type = EVENT_UPDATE_LABEL,
                        .data.update_label = {
                            .label = ui_temperatureLabel
                        }
                    };
                    snprintf(gui_msg.data.update_label.text, sizeof(gui_msg.data.update_label.text), "%2.1f \u00b0C", event.data.temp_reading.temperature);
                    xQueueSend(xAppEventQueue, &gui_msg, portMAX_DELAY);
                    break;
                }
                case EVENT_TEMP_SET:
                {
                    AppEvent gui_msg = {
                        .type = EVENT_UPDATE_LABEL,
                        .data.update_label = {
                            .label = ui_SetTemperature
                        }
                    };
                    snprintf(gui_msg.data.update_label.text, sizeof(gui_msg.data.update_label.text), "%d \u00b0C", event.data.temp_set.temperature);
                    xQueueSend(xAppEventQueue, &gui_msg, portMAX_DELAY);
                    break;
                }

                default:
                    printf("Unknown event type: %d\n", event.type);
                    break;
            }
        }
    }
}
