set(COMPONENT_SRCS "wifi_manager.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_REQUIRES esp_wifi esp_event esp_netif nvs_flash freertos comms)

register_component()