/**
 * @file board_pins.h
 * 
 * @brief Board-specific GPIO definitions.
 */

#ifndef __BOARD_PINS_H__
#define __BOARD_PINS_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "sdkconfig.h"

//---------------------------------- MACROS -----------------------------------

#ifdef CONFIG_TARGET_BYTELAB

#define GPIO_LED_RED    (26U)
#define GPIO_LED_GREEN  (27U)
#define GPIO_LED_BLUE   (14U)

#define GPIO_BUTTON_1   (36U)
#define GPIO_BUTTON_2   (32U)
#define GPIO_BUTTON_3   (33U)
#define GPIO_BUTTON_4   (25U)

#define GPIO_JOY_X      (34U)
#define GPIO_JOY_Y      (35U)

#define GPIO_UART_RX    (3U)
#define GPIO_UART_TX    (1U)

#define GPIO_I2C_SCL    (21U)
#define GPIO_I2C_SDA    (22U)

#elif defined(CONFIG_TARGET_VIDI)

#define GPIO_LED_RED    (40U) // Doesn't exist
#define GPIO_LED_GREEN  (41U) // Doesn't exist
#define GPIO_LED_BLUE   (2U)

#define GPIO_BUTTON_1   (27U)
#define GPIO_BUTTON_2   (39U)
#define GPIO_BUTTON_3   (32U)
#define GPIO_BUTTON_4   (33U)

#define GPIO_JOY_X      (34U)
#define GPIO_JOY_Y      (35U)

#define GPIO_UART_RX    (3U)
#define GPIO_UART_TX    (1U)

#define GPIO_I2C_SCL    (21U)
#define GPIO_I2C_SDA    (22U)

#endif

#define GPIO_BIT_MASK(X) ((1ULL << (X)))

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PUBLIC FUNCTION PROTOTYPES ---------------------------

#ifdef __cplusplus
}
#endif

#endif // __BOARD_PINS_H__
