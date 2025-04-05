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

#define DELAY_TIME_MS_DEBOUNCE (50U)

// Extern volatile variables for button press counts.
// Use 'volatile' because they are modified within an ISR.
extern volatile uint32_t button_press_count[4];

esp_err_t button1_init(void);
esp_err_t button2_init(void);
esp_err_t button3_init(void);
esp_err_t button4_init(void);

#endif // BUTTON_H
