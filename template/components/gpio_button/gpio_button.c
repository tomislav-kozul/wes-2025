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
#include "freertos/timers.h"

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
static void _btn_1_cb(TimerHandle_t xTimer);
static void _btn_2_cb(TimerHandle_t xTimer);
static void _btn_3_cb(TimerHandle_t xTimer);
static void _btn_4_cb(TimerHandle_t xTimer);

static TimerHandle_t buttonTimer1 = NULL;
static TimerHandle_t buttonTimer2 = NULL;
static TimerHandle_t buttonTimer3 = NULL;
static TimerHandle_t buttonTimer4 = NULL;
//------------------------------- GLOBAL DATA ---------------------------------
volatile uint32_t button_press_count[4] = {0};


//------------------------------ PUBLIC FUNCTIONS -----------------------------
esp_err_t button_init(uint8_t pin, void (*p_isr)(void*), TimerHandle_t *p_timer, TimerCallbackFunction_t timer_cb)
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

    if (ESP_OK == err)
    {
        *p_timer = xTimerCreate("btn_timer", pdMS_TO_TICKS(DELAY_TIME_MS_DEBOUNCE), pdFALSE, NULL, timer_cb);
        if (*p_timer == NULL)
        {
            return ESP_FAIL;
        }
    }

    return err;
}

esp_err_t button1_init(void)
{
    return button_init(GPIO_BUTTON_1, _btn_1_isr, &buttonTimer1, _btn_1_cb);
}

esp_err_t button2_init(void)
{
    return button_init(GPIO_BUTTON_2, _btn_2_isr, &buttonTimer2, _btn_2_cb);
}

esp_err_t button3_init(void)
{
    return button_init(GPIO_BUTTON_3, _btn_3_isr, &buttonTimer3, _btn_3_cb);
}

esp_err_t button4_init(void)
{
    return button_init(GPIO_BUTTON_4, _btn_4_isr, &buttonTimer4, _btn_4_cb);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _btn_1_cb(TimerHandle_t xTimer)
{
    if (gpio_get_level(GPIO_BUTTON_1))
    {
        button_press_count[0]++;
        printf("BTN1 pressed. Count = %lu\n", (unsigned long)button_press_count[0]);
    }
}

static void _btn_2_cb(TimerHandle_t xTimer)
{
    if (gpio_get_level(GPIO_BUTTON_2))
    {
        button_press_count[1]++;
        printf("BTN2 pressed. Count = %lu\n", (unsigned long)button_press_count[1]);
    }
}


static void _btn_3_cb(TimerHandle_t xTimer)
{
    if (gpio_get_level(GPIO_BUTTON_3))
    {
        button_press_count[2]++;
        printf("BTN3 pressed. Count = %lu\n", (unsigned long)button_press_count[2]);
    }
}

static void _btn_4_cb(TimerHandle_t xTimer)
{
    if (gpio_get_level(GPIO_BUTTON_4))
    {
        button_press_count[3]++;
        printf("BTN4 pressed. Count = %lu\n", (unsigned long)button_press_count[3]);
    }
}
//---------------------------- INTERRUPT HANDLERS ------------------------------
static void IRAM_ATTR _btn_1_isr(void *p_arg)
{
    BaseType_t hp_task = pdFALSE;
    xTimerResetFromISR(buttonTimer1, &hp_task);
    //if (hp_task) portYIELD_FROM_ISR();
}

static void IRAM_ATTR _btn_2_isr(void *p_arg)
{
    BaseType_t hp_task = pdFALSE;
    xTimerResetFromISR(buttonTimer2, &hp_task);
    //if (hp_task) portYIELD_FROM_ISR();
}

static void IRAM_ATTR _btn_3_isr(void *p_arg)
{
    BaseType_t hp_task = pdFALSE;
    xTimerResetFromISR(buttonTimer3, &hp_task);
    //if (hp_task) portYIELD_FROM_ISR();
}

static void IRAM_ATTR _btn_4_isr(void *p_arg)
{
    BaseType_t hp_task = pdFALSE;
    xTimerResetFromISR(buttonTimer4, &hp_task);
    //if (hp_task) portYIELD_FROM_ISR();
}