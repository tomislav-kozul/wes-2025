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

#include "comms.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief Callback function for button 1 press.
 *
 * @param [in] p_arg Pointer to the pin that caused the callback.
 */
static void _btn_1_isr(void *p_arg);

/**
 * @brief Callback function for button 2 press.
 *
 * @param [in] p_arg Pointer to the pin that caused the callback.
 */
static void _btn_2_isr(void *p_arg);

/**
 * @brief Callback function for button 3 press.
 *
 * @param [in] p_arg Pointer to the pin that caused the callback.
 */
static void _btn_3_isr(void *p_arg);

/**
 * @brief Callback function for button 4 press.
 *
 * @param [in] p_arg Pointer to the pin that caused the callback.
 */
static void _btn_4_isr(void *p_arg);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static void _button_timer_cb(TimerHandle_t xTimer);
static TimerHandle_t buttonTimer = NULL;

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
    esp_err_t err = button_init(GPIO_BUTTON_1, _btn_1_isr);

    if (err == ESP_OK)
    {
        // Create a one-shot timer for debouncing
        // e.g. 50 ms for debounce
        buttonTimer = xTimerCreate(
            "buttonTimer",
            pdMS_TO_TICKS(DELAY_TIME_MS_DEBOUNCE),
            pdFALSE,       // one-shot timer
            NULL,
            _button_timer_cb
        );

        if (buttonTimer == NULL)
        {
            //ESP_LOGE("BTN", "Failed to create debounce timer");
            return ESP_FAIL;
        }
    }
    return err;
}

esp_err_t button2_init(void)
{
    return button_init(GPIO_BUTTON_2, _btn_2_isr);
}

esp_err_t button3_init(void)
{
    return button_init(GPIO_BUTTON_3, _btn_3_isr);
}

esp_err_t button4_init(void)
{
    return button_init(GPIO_BUTTON_4, _btn_4_isr);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _button_timer_cb(TimerHandle_t xTimer)
{
    // Read the actual state of the pin
    int level = gpio_get_level(GPIO_BUTTON_1);

    // If the pin is still high (or low, depending on your wiring),
    // we consider that a stable press
    if (level == 1) // e.g. if pressed means logic 1
    {
        button1_press_count++;
        xEventGroupSetBits(
            xGuiButtonEventGroup,   /* The event group being updated. */
            GPIO_BUTTON_1_PRESS);   /* The bits being set. */
        printf("Count=%lu\n", button1_press_count);
    }
    else
    {
        // Not a valid press
    }
}

//---------------------------- INTERRUPT HANDLERS ------------------------------
// Interrupt Service Routine for button 1.
static void IRAM_ATTR _btn_1_isr(void *p_arg)
{
    (void)p_arg; // Suppress unused parameter warning
    //button1_press_count++;  // Increment the button 1 counter
    if (buttonTimer != NULL)
    {
        // Reset will (re)start the timer, making it fire 50ms from now
        xTimerResetFromISR(buttonTimer, pdFALSE);
    }
}

// Interrupt Service Routine for button 2.
static void IRAM_ATTR _btn_2_isr(void *p_arg)
{
    (void)p_arg; // Suppress unused parameter warning
    button1_press_count++;  // Increment the button 1 counter
}

// Interrupt Service Routine for button 3.
static void IRAM_ATTR _btn_3_isr(void *p_arg)
{
    (void)p_arg; // Suppress unused parameter warning
    button1_press_count++;  // Increment the button 1 counter
}

// Interrupt Service Routine for button 4.
static void IRAM_ATTR _btn_4_isr(void *p_arg)
{
    (void)p_arg; // Suppress unused parameter warning
    button1_press_count++;  // Increment the button 1 counter
}