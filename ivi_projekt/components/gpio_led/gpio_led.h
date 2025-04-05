/**
 * @file gpio_led.h
 *
 * @brief Header file for LED control library.
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

 #ifndef GPIO_LED_H_
 #define GPIO_LED_H_
 
 //--------------------------------- INCLUDES ----------------------------------
 #include <stdint.h> // for uint8_t
 
 //---------------------------------- MACROS -----------------------------------

 //---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
 /**
  * @brief This function initializes received GPIO pin as an output.
  *
  * @param [in] pin GPIO number to be initialized.
  */
 void led_init(uint8_t pin);
 
 /**
  * @brief This function turns on the LED.
  *
  * @param [in] pin The GPIO pin number (that controls LED) to be turned on.
  */
 void led_on(uint8_t pin);
 
 /**
  * @brief This function turns off the LED.
  *
  * @param [in] pin The GPIO pin number (that controls LED) to be turned off.
  */
 void led_off(uint8_t pin);

  /**
  * @brief This function toggles the LED.
  *
  * @param [in] pin The GPIO pin number (that controls LED) to be toggled.
  */
 void led_toggle(uint8_t pin);

 void led_toggle_state_init(void);
 
 #endif /* LED_CONTROL_H_ */