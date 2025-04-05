#include "sht3x.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "comms.h"

#define UART_STACK_SIZE             (4096)

#define INIT_DELAY 1000
#define SLEEP_DELAY 1000

static const char *SENSORS_TAG = "sensors";

char scale = SCALE_CELCIUS;
float temperature = 0.0;
float humidity = 0.0;

void _temp_sensor_task(void *arg) {
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };

    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &i2c_config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, i2c_config.mode,
                    I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0));

    esp_log_level_set(SENSORS_TAG, ESP_LOG_INFO);

    #if defined(SENSORS_SCALE_F)
    scale = SCALE_FAHRENHEIT;
    #elif defined(SENSORS_SCALE_K)
    scale = SCALE_KELVIN;
    #endif

    vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);

    for(;;) {
        sht3x_start_periodic_measurement();

        sht3x_sensors_values_t sensors_values = {
            .temperature = 0x00,
            .humidity = 0x00
        };
        vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);

        if(sht3x_read_measurement(&sensors_values) != ESP_OK) {
            ESP_LOGE(SENSORS_TAG, "Sensors read measurement error!");
        }
        vTaskDelay(INIT_DELAY / portTICK_PERIOD_MS);

        float temperature = sensors_values.temperature;
        float humidity = sensors_values.humidity;

        #if defined(SENSORS_SCALE_F)
        temperature = FAHRENHEIT(temperature);
        #elif defined(SENSORS_SCALE_K)
        temperature = KELVIN(temperature);
        #endif

        ESP_LOG_BUFFER_HEX_LEVEL(SENSORS_TAG, &sensors_values, sizeof(sensors_values), ESP_LOG_DEBUG);

        sht3x_stop_periodic_measurement();

        ESP_LOGI(SENSORS_TAG, "Temperature %2.1f °%c - Humidity %2.1f%%", temperature, scale, humidity);
        xQueueSend(xTempReadingQueue, ( void * ) &temperature, portMAX_DELAY);
        vTaskDelay(SLEEP_DELAY / portTICK_PERIOD_MS);
    }
}

void temp_sensor_task_init() {
    xTaskCreate(_temp_sensor_task, "temp_sensor_task", UART_STACK_SIZE, NULL, configMAX_PRIORITIES-9, NULL);
}
