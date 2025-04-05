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


#define USER_INTERFACE_QUEUE_SIZE (20U)

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief Enums hold gui app events.
 *
 */
typedef struct
{
    lv_obj_t *label; // Label name
    int data;              // Integer data to be passed
} LabelData;

//------------------------------- GLOBAL DATA ---------------------------------
extern EventGroupHandle_t xGuiButtonEventGroup;
extern EventGroupHandle_t xGpioButtonEventGroup;
extern QueueHandle_t xGuiUpdateQueue;

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
 