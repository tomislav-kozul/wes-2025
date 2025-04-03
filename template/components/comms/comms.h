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
#include "freertos/event_groups.h"

//---------------------------------- MACROS -----------------------------------
#define GUI_APP_EVENT_BUTTON_JEBENI_PRESSED (1 << 0)

//-------------------------------- DATA TYPES ---------------------------------

//------------------------------- GLOBAL DATA ---------------------------------
extern EventGroupHandle_t xGuiButtonEventGroup;

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
 