/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

struct spi_m_sync_descriptor WINC_SPI;

struct usart_sync_descriptor EDBG_UART;

void WINC_IRQ_init(void)
{
	_gclk_enable_channel(EIC_GCLK_ID, CONF_GCLK_EIC_SRC);

	// Set pin direction to input
	gpio_set_pin_direction(PA21, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA21,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA21, PINMUX_PA21A_EIC_EXTINT5);

	ext_irq_init();
}

void WINC_SPI_PORT_init(void)
{

	gpio_set_pin_level(PA16,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PA16, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PA16, PINMUX_PA16C_SERCOM1_PAD0);

	gpio_set_pin_level(PA17,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PA17, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PA17, PINMUX_PA17C_SERCOM1_PAD1);

	// Set pin direction to input
	gpio_set_pin_direction(PA19, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA19,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA19, PINMUX_PA19C_SERCOM1_PAD3);
}

void WINC_SPI_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM1);
	_gclk_enable_channel(SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC);
}

void WINC_SPI_init(void)
{
	WINC_SPI_CLOCK_init();
	spi_m_sync_init(&WINC_SPI, SERCOM1);
	WINC_SPI_PORT_init();
}

void EDBG_UART_PORT_init(void)
{

	gpio_set_pin_function(EDBG_UART_TX, PINMUX_PA22C_SERCOM3_PAD0);

	gpio_set_pin_function(EDBG_UART_RX, PINMUX_PA23C_SERCOM3_PAD1);
}

void EDBG_UART_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM3);
	_gclk_enable_channel(SERCOM3_GCLK_ID_CORE, CONF_GCLK_SERCOM3_CORE_SRC);
}

void EDBG_UART_init(void)
{
	EDBG_UART_CLOCK_init();
	usart_sync_init(&EDBG_UART, SERCOM3, (void *)NULL);
	EDBG_UART_PORT_init();
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA02

	gpio_set_pin_level(WINC_PIN_RESET,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(WINC_PIN_RESET, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(WINC_PIN_RESET, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA03

	gpio_set_pin_level(WINC_PIN_CHIP_ENABLE,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(WINC_PIN_CHIP_ENABLE, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(WINC_PIN_CHIP_ENABLE, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA18

	gpio_set_pin_level(WINC_PIN_CHIP_SELECT,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(WINC_PIN_CHIP_SELECT, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(WINC_PIN_CHIP_SELECT, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB03

	gpio_set_pin_level(XB1_PWR_PIN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output

	WINC_IRQ_init();

	WINC_SPI_init();

	EDBG_UART_init();

	delay_driver_init();
        
        gpio_set_pin_direction(XB1_PWR_PIN, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(XB1_PWR_PIN, GPIO_PIN_FUNCTION_OFF);

}
