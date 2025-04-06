#include "hvac.h"
#include "comms.h"
#include "pins.h"
#include "gpio_led.h"
#include <stdio.h>

static TaskHandle_t p_gui_updater_task = NULL;

static void _hvac_task(void *p_parameter);

void hvac_task_init(void)
{
    xTaskCreate(_hvac_task, "gui_updater", 4096 * 2, NULL, 5, &p_gui_updater_task);
}

static void _hvac_task(void *p_parameter)
{
    AppEvent event;
    AppEvent eventToRemove;
    int acTempSet = 24;
    float ambientTemp = 0.0;
    bool acOn = false;

    for (;;) {
        if (xQueuePeek(xAppEventQueue, &event, portMAX_DELAY)) {
            switch (event.type) {
                case HVAC_AC_ON_OFF:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    acOn = ! acOn;
                    printf("onoffevent");
                    break;
                case HVAC_AC_TEMP_UPDATE:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    acTempSet = event.data.temp_set.temperature;
                    break;
                case HVAC_AMBIENT_TEMP_UPDATE:
                    xQueueReceive(xAppEventQueue, &eventToRemove, 0);
                    ambientTemp = event.data.temp_reading.temperature;
                    break; 
                default:
                    break;
            }
        }

        printf("%d\n", acTempSet);
        printf("%2.1f\n", ambientTemp);
        printf("%d\n", acOn);

        if (acOn && acTempSet < ambientTemp) {
            led_on(GPIO_LED_BLUE);
        } else {
            led_off(GPIO_LED_BLUE);
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
