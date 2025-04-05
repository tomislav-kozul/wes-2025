/**
 * @file comms.h
 *
 * @brief See the source file.
 */

 #ifndef __COMMS_H__
 #define __COMMS_H__
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 //--------------------------------- INCLUDES ----------------------------------
 #include "freertos/FreeRTOS.h"
 #include "freertos/queue.h"
 #include "freertos/event_groups.h"
 #include "ui_helpers.h"
 
 //---------------------------------- MACROS -----------------------------------
 #define GUI_APP_EVENT_BUTTON_JEBENI_PRESSED (1 << 0)
 
 #define GPIO_BUTTON_1_PRESS     (1 << 1)
 #define GPIO_BUTTON_2_PRESS     (1 << 2)
 #define GPIO_BUTTON_3_PRESS     (1 << 3)
 #define GPIO_BUTTON_4_PRESS     (1 << 4)
 
 #define WIFI_CONNECTED_BIT      (1 << 5)

 #define FRONT_SENSOR_ZONE_RED       (1 << 10)
 #define FRONT_SENSOR_ZONE_YELLOW    (1 << 11)
 #define FRONT_SENSOR_ZONE_GREEN     (1 << 12)
 #define FRONT_SENSOR_ZONE_NONE      (1 << 13)
 
 
 #define USER_INTERFACE_QUEUE_SIZE (20U)
 
 //-------------------------------- DATA TYPES ---------------------------------
 /**
  * @brief Enums hold gui app events.
  *
  */
 
 typedef enum {
    GUI_CMD_UPDATE_LABEL
} GuiCommandType;
 
 typedef struct {
     GuiCommandType command_type;
     union {
        struct {
            lv_obj_t *label;
            char text[32];
        } update_label;
     };
 } GuiMessage;

 typedef struct
 {
     lv_obj_t *label; // Label name
     int data;              // Integer data to be passed
 } LabelData;

 typedef struct 
 {
     lv_obj_t *container_red;
     lv_obj_t *container_yellow;
     lv_obj_t *container_green;
     int data_red;
     int data_yellow;
     int data_green;
 } sensorAlphaUpdate;
 
 
 //------------------------------- GLOBAL DATA ---------------------------------
 extern EventGroupHandle_t xGuiButtonEventGroup;
 extern EventGroupHandle_t xGpioButtonEventGroup;
 extern QueueHandle_t xGuiUpdateQueue;
 extern QueueHandle_t xTempReadingQueue;
 extern QueueHandle_t xTempSetQueue;
 
 //---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
 /**
  * @brief The function initializes communication interfaces like queues and
  * event groups.
  *
  */
 void comms_init(void);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif // __COMMS_H__
  
