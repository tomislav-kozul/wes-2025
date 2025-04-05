#include <esp_event.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include <stdio.h>
#include "comms.h"
#include <esp_sntp.h>
#include <time.h>
#include <sys/time.h>
//#include "wifi_manager.h"

static const char *TAG = "wifi_manager";

// Forward declarations
static esp_err_t _wifi_nvs_init(void);
static void _wifi_event_handler(void *arg, esp_event_base_t event_base,
                                int32_t event_id, void *event_data);
static void initialize_sntp(void);
static void sntp_wait_for_sync(void);

/**************************************************/
esp_err_t wifi_manager_init_sta(void)
{
    esp_err_t ret;

    // 1. Initialize NVS if not done elsewhere
    ret = _wifi_nvs_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "NVS init failed");
        return ret;
    }

    // 2. Initialize TCP/IP stack
    ESP_ERROR_CHECK(esp_netif_init());

    // 3. Create default event loop if not created
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // 4. Create default station
    esp_netif_create_default_wifi_sta();

    // 5. Initialize Wi-Fi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // 6. Register Wi-Fi and IP event handlers
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                    &_wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                    &_wifi_event_handler, NULL));

    // 7. Set Wi-Fi mode to STA
    ESP_LOGI(TAG, "Setting Wi-Fi mode to STA");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    // 8. Start Wi-Fi
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "Wi-Fi STA initialized.");

    return ESP_OK;
}

/**************************************************/
esp_err_t wifi_manager_connect(const char *ssid, const char *password)
{
    if (!ssid || !password) {
        ESP_LOGE(TAG, "Invalid SSID or password");
        return ESP_ERR_INVALID_ARG;
    }

    // Prepare station config
    wifi_config_t wifi_config = {0};

    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);

    strncpy((char*)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char*)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);

    ESP_LOGI(TAG, "Connecting to SSID: %s", ssid);
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_connect());
    return ESP_OK;
}

/**************************************************/
static esp_err_t _wifi_nvs_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    return ret;
}

/**************************************************/
static void _wifi_event_handler(void *arg, esp_event_base_t event_base,
                                int32_t event_id, void *event_data)
{
    if ((event_base == WIFI_EVENT) && (event_id == WIFI_EVENT_STA_START)) {
        ESP_LOGI(TAG, "Wi-Fi STA started; you may connect now.");
        // You could optionally call esp_wifi_connect() here if not done outside.
    }
    else if ((event_base == WIFI_EVENT) && (event_id == WIFI_EVENT_STA_DISCONNECTED)) {
        ESP_LOGW(TAG, "Disconnected. Trying to reconnect...");
        esp_wifi_connect();
    }
    else if ((event_base == IP_EVENT) && (event_id == IP_EVENT_STA_GOT_IP)) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
    
        // Notify UI
        xEventGroupSetBits(xGuiButtonEventGroup, WIFI_CONNECTED_BIT);
    
        // Start SNTP sync
        initialize_sntp();
        sntp_wait_for_sync();
    }
}

static void initialize_sntp(void)
{
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");  // Or your local NTP server
    sntp_init();
    ESP_LOGI(TAG, "SNTP initialized");
}

static void sntp_wait_for_sync(void)
{
    for (int i = 0; i < 10; ++i) {
        if (sntp_get_sync_status() == SNTP_SYNC_STATUS_COMPLETED) {
            ESP_LOGI(TAG, "Time synchronized.");
            
            break;
        }
        ESP_LOGI(TAG, "Waiting for time sync... (%d/10)", i+1);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
