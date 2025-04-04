/**
* @file gui_updater.c

* @brief This file is responsible for updating the elements on screen.
*/

//--------------------------------- INCLUDES ----------------------------------
#include "comms.h"
#include "ui_helpers.h"
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief Starts GUI updater task.
 *
 * @param [in] p_parameter Parameter that is passed to the task.
 */
static void _gui_updater_task(void *p_parameter);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static TaskHandle_t p_gui_updater_task = NULL;

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
/**
 * @brief Initializes the GUI updater.
 */
void gui_updater_init(void)
{
    xTaskCreate(_gui_updater_task, "gui_updater", 4096 * 2, NULL, 5, &p_gui_updater_task);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _gui_updater_task(void *p_parameter) {
    LabelData receivedData;

    for (;;)
    {
        // Wait for data from the queue
        if (xQueueReceive(xGuiUpdateQueue, &receivedData, portMAX_DELAY)) {
            // Print the label and data (assuming lv_label_set_text_fmt function)
            lv_label_set_text_fmt(receivedData.label, "%d", receivedData.data);
            
        }
    }
}
//---------------------------- INTERRUPT HANDLERS -----------------------------

