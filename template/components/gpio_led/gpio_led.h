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
 
 #include <stdint.h> // for uint8_t
 
 //---------------------------------- MACROS -----------------------------------
 #define GPIO_BIT_MASK(X) ((1ULL << (X)))
 
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
 
 #endif /* LED_CONTROL_H_ */