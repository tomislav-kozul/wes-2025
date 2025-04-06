#ifndef __COMMS_H__
#define __COMMS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "lvgl.h"

#define USER_INTERFACE_QUEUE_SIZE (20U)

// Event type enumeration
typedef enum {
    EVENT_GUI_BUTTON_PRESSED,
    EVENT_GPIO_BUTTON_1,
    EVENT_GPIO_BUTTON_2,
    EVENT_GPIO_BUTTON_3,
    EVENT_GPIO_BUTTON_4,
    EVENT_AC_ON_OFF,
    EVENT_FRONT_SENSOR_GREEN,
    EVENT_FRONT_SENSOR_YELLOW,
    EVENT_FRONT_SENSOR_RED,
    EVENT_FRONT_SENSOR_NONE,
    EVENT_TEMP_READING,
    EVENT_AC_TEMP_SET,
    EVENT_UPDATE_LABEL,
    EVENT_UPDATE_SENSOR_ALPHA,
    EVENT_AC_TEMP_UPDATE,
    EVENT_AMBIENT_TEMP_UPDATE,
    HVAC_AC_TEMP_UPDATE,
    HVAC_AC_ON_OFF,
    HVAC_AMBIENT_TEMP_UPDATE
} AppEventType;

// Unified event structure
typedef struct {
    AppEventType type;
    union {
        struct {
            float temperature;
        } temp_reading;

        struct {
            int temperature;
        } temp_set;

        struct {
            lv_obj_t *label;
            char text[32];
        } update_label;

        struct {
            lv_obj_t *container_red;
            lv_obj_t *container_yellow;
            lv_obj_t *container_green;
            int data_red;
            int data_yellow;
            int data_green;
        } sensor_alpha;
    } data;
} AppEvent;

//-------------------------------- DATA TYPES ---------------------------------
typedef enum {
    LABEL_TYPE_TEXT,
    LABEL_TYPE_INT
} LabelType;

typedef struct {
    lv_obj_t* label;
    LabelType label_type;
    union {
        char text[32];  // For date, time, etc.
        int value;      // For counters, numeric values
    } content;
} LabelData;

// Global queue handle
extern QueueHandle_t xAppEventQueue;
extern QueueHandle_t xGuiUpdateQueue;

// Initialization function
void comms_init(void);

#ifdef __cplusplus
}
#endif

#endif // __COMMS_H__
