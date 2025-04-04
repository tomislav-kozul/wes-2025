/**
 * @file gpio_button.c
 *
 * @brief Source file for BUTTON control library.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

 //--------------------------------- INCLUDES ----------------------------------
#include "gpio_button.h"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief Callback function for button 1 press.
 *
 * @param [in] p_arg Pointer to the pin that caused the callback.
 */
static void _btn_1_isr(void *p_arg);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------
volatile uint32_t button1_press_count = 0;

//------------------------------ PUBLIC FUNCTIONS -----------------------------
esp_err_t button_init(uint8_t pin, void (*p_isr)(void*))
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << pin),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_POSEDGE,
    };

    esp_err_t err = gpio_config(&io_conf);
    if (ESP_OK == err)
    {
        err = gpio_set_intr_type(io_conf.pin_bit_mask, io_conf.intr_type);
    }

    if (ESP_OK == err)
    {
        // Install the ISR service (install only once in a real application)
        gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
    }

    if (ESP_OK == err)
    {
        err = gpio_isr_handler_add(pin, p_isr, (void *)&pin);
    }

    return err;
}

// Helper function to initialize button 1 with its ISR.
esp_err_t button1_init(void)
{
    return button_init(GPIO_BUTTON_1, _btn_1_isr);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS ------------------------------
// Interrupt Service Routine for button 1.
static void IRAM_ATTR _btn_1_isr(void *p_arg)
{
    (void)p_arg; // Suppress unused parameter warning
    button1_press_count++;  // Increment the button 1 counter
}