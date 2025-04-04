/**
 * @file gpio_button.h
 *
 * @brief Header file for button control library.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef GPIO_BUTTON_H_
#define GPIO_BUTTON_H_

#include "esp_err.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

// Button GPIO definitions
#define GPIO_BUTTON_1 (36U)
#define GPIO_BUTTON_2 (32U)
#define GPIO_BUTTON_3 (33U)
#define GPIO_BUTTON_4 (25U)
#define GPIO_BIT_MASK(X) ((1ULL << (X)))

#define DELAY_TIME_MS_DEBOUNCE (50U)

// Extern volatile variables for button press counts.
// Use 'volatile' because they are modified within an ISR.
extern volatile uint32_t button1_press_count;

esp_err_t button1_init(void);
esp_err_t button2_init(void);
esp_err_t button3_init(void);
esp_err_t button4_init(void);

#endif // BUTTON_H
