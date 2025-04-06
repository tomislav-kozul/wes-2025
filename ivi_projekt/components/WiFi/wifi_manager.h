#ifndef __WIFI_MANAGER_H__
#define __WIFI_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"


/**
 * @brief Initializes Wi-Fi in station mode.
 *        (Sets up netif, starts Wi-Fi, etc.)
 * 
 * @return esp_err_t 
 */
esp_err_t wifi_manager_init_sta(void);

/**
 * @brief Connects to the given SSID/PWD. Typically called after wifi_manager_init_sta().
 * 
 * @param ssid      The Wi-Fi SSID to connect to.
 * @param password  The Wi-Fi password.
 * @return esp_err_t
 */
esp_err_t wifi_manager_connect(const char *ssid, const char *password);

#ifdef __cplusplus
}
#endif

#endif // __WIFI_MANAGER_H__