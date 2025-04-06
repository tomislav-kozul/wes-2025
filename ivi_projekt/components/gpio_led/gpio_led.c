/**
 * @file gpio_led.c
 *
 * @brief Source file for LED control library.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "gpio_led.h"
#include "driver/gpio.h"

#include "pins.h"

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static uint8_t led_state_red;
static uint8_t led_state_blue;
static uint8_t led_state_green;

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void led_toggle_state_init(void) {
    led_state_red = 0;
    led_state_blue = 0;
    led_state_green = 0;
}

void led_init(uint8_t pin)
{
    // zero-initialize the config structure.
    gpio_config_t io_conf = {};
    // disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    // set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    // bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_BIT_MASK(pin);
    // disable pull-down mode
    io_conf.pull_down_en = 0;
    // disable pull-up mode
    io_conf.pull_up_en = 0;
    // configure GPIO with the given settings
    gpio_config(&io_conf);
}

void led_on(uint8_t pin)
{
    gpio_set_level(pin, 1U);
}

void led_off(uint8_t pin)
{
    gpio_set_level(pin, 0U);
}

void led_toggle(uint8_t pin)
{
    uint32_t level = 0;
    switch (pin)
    {
        case GPIO_LED_BLUE:
            led_state_blue = (led_state_blue + 1) % 2;
            level = led_state_blue;
            break;
        case GPIO_LED_RED:
            led_state_red = (led_state_red + 1) % 2;
            level = led_state_red;
            break;
        case GPIO_LED_GREEN:
            led_state_green = (led_state_green + 1) % 2;
            level  = led_state_green;
            break;
        default:
            printf("Invalid LED pin!\n");
            break;
    }

    gpio_set_level(pin, level);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS ------------------------------