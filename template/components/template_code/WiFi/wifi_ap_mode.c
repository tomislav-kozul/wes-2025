/**
 * @file app_main.c
 *
 * @brief Wifi access point example.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_mac.h"

#include "lwip/err.h"
#include "lwip/sys.h"

//---------------------------------- MACROS -----------------------------------
#define EXAMPLE_ESP_WIFI_SSID    ("WESSoftAP")
#define EXAMPLE_ESP_WIFI_PASS    ("wes123456")
#define EXAMPLE_ESP_WIFI_CHANNEL (1U)
#define EXAMPLE_MAX_STA_CONN     (4U)

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief It's a callback function that is called when an event occurs.
 *
 * @param [in] p_arg This is a pointer to the argument passed to the event handler.
 * @param [in] event_base The event base that the event is associated with.
 * @param [in] event_id The event ID.
 * @param [in] p_event_data This is the data that is passed to the event handler.
 */
static void _event_handler(void *p_arg, esp_event_base_t event_base, int32_t event_id, void *p_event_data);

/**
 * @brief It initializes the ESP32 in AP mode.
 *
 * @return The error code of the last function call.
 */
static esp_err_t _wifi_init_softap(void);

/**
 * @brief If the NVS partition is not initialized, initialize it.
 *
 * @return The return value is the bitwise OR of the return values of nvs_flash_erase() and
 * nvs_flash_init().
 */
static esp_err_t _nvs_init(void);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static const char *TAG = "WIFI";

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

void app_main(void)
{
    // Initialize NVS
    esp_err_t err = ESP_OK;

    /* Initialize NVS partition */
    err = _nvs_init();

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
        err = _wifi_init_softap();
    }

    if(ESP_OK != err)
    {
        ESP_LOGE(TAG, "Init failed");
    }

    vTaskSuspend(NULL);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

static esp_err_t _wifi_init_softap(void)
{
    esp_err_t err = ESP_OK;

    if(ESP_OK == err)
    {
        /* Initialize TCP/IP */
        ESP_LOGI(TAG, " Initialize TCP/IP");
        err = esp_netif_init();
    }

    if(ESP_OK == err)
    {
        /* Initialize the event loop */
        ESP_LOGI(TAG, " Initialize the event loop");
        err = esp_event_loop_create_default();
    }

    if(ESP_OK == err)
    {
        /* Create default wifi AP */
        ESP_LOGI(TAG, " Create default wifi AP");
        esp_netif_create_default_wifi_ap();
    }

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, " ESP Wifi init");
        err = esp_wifi_init(&cfg);
    }

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, " Set up event handler");
        err = esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &_event_handler, NULL, NULL);
    }

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
          },
    };

    if(0 == strlen(EXAMPLE_ESP_WIFI_PASS))
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    if(ESP_OK == err)
    {
        /* Set wifi mode: AP */
        ESP_LOGI(TAG, " Set wifi mode: AP");
        err = esp_wifi_set_mode(WIFI_MODE_AP);
    }

    if(ESP_OK == err)
    {
        /* Set wifi config: AP */
        ESP_LOGI(TAG, " Set wifi config for AP");
        err = esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    }

    if(ESP_OK == err)
    {
        /* Start wifi in AP mode */
        ESP_LOGI(TAG, " Start wifi in AP mode");
        err = esp_wifi_start();
        ESP_LOGI(TAG,
                 "wifi_init_softap finished. SSID:%s password:%s channel:%d",
                 EXAMPLE_ESP_WIFI_SSID,
                 EXAMPLE_ESP_WIFI_PASS,
                 EXAMPLE_ESP_WIFI_CHANNEL);
    }

    return err;
}

static esp_err_t _nvs_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if((ESP_ERR_NVS_NO_FREE_PAGES == ret) || (ESP_ERR_NVS_NEW_VERSION_FOUND == ret))
    {
        /* NVS partition was truncated
         * and needs to be erased */
        ret = nvs_flash_erase();

        /* Retry nvs_flash_init */
        ret |= nvs_flash_init();
    }
    return ret;
}

//---------------------------- INTERRUPT HANDLERS -----------------------------

static void _event_handler(void *p_arg, esp_event_base_t event_base, int32_t event_id, void *p_event_data)
{
    if(WIFI_EVENT_AP_STACONNECTED == event_id)
    {
        wifi_event_ap_staconnected_t *p_event = (wifi_event_ap_staconnected_t *)p_event_data;
        ESP_LOGI(TAG, "station " MACSTR " JOIN, AID=%d", MAC2STR(p_event->mac), p_event->aid);
    }
    else if(WIFI_EVENT_AP_STADISCONNECTED == event_id)
    {
        wifi_event_ap_stadisconnected_t *p_event = (wifi_event_ap_stadisconnected_t *)p_event_data;
        ESP_LOGI(TAG, "station " MACSTR " LEAVE, AID=%d", MAC2STR(p_event->mac), p_event->aid);
    }
    else
    {
        // Ignore.
    }
}
