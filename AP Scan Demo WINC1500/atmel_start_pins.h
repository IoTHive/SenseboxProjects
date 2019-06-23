/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define WINC_PIN_RESET GPIO(GPIO_PORTA, 2)
#define WINC_PIN_CHIP_ENABLE GPIO(GPIO_PORTA, 3)
#define WINC_PIN_IRQ GPIO(GPIO_PORTA, 21)
#define PA16 GPIO(GPIO_PORTA, 16)
#define PA17 GPIO(GPIO_PORTA, 17)
#define WINC_PIN_CHIP_SELECT GPIO(GPIO_PORTA, 18)
#define PA19 GPIO(GPIO_PORTA, 19)
#define PA21 GPIO(GPIO_PORTA, 21)
#define EDBG_UART_TX GPIO(GPIO_PORTA, 22)
#define EDBG_UART_RX GPIO(GPIO_PORTA, 23)
#define XB1_PWR_PIN GPIO(GPIO_PORTB, 3)

#endif // ATMEL_START_PINS_H_INCLUDED
