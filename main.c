/** \file main.c
 * \brief Sample LPC1114 project
 * \details This file holds a very basic code for LPC1114. This code configures
 * flash access time, enables the PLL and all required clocks and peripherals
 * to achieve the highest allowed frequency for LPC1114 (50MHz). Main code
 * block just blinks the LED. The LED port and pin are defined in config.h
 * file. Target core frequency and quartz crystal resonator frequency are
 * defined there as well.
 *
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-08
 */

/******************************************************************************
* project: lpc1114_blink_led
* chip: LPC1114
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
*
* prefix: (none)
*
* available global functions:
* 	int main(void)
*
* available local functions:
* 	static void flash_access_time(uint32_t frequency)
* 	static uint32_t pll_start(uint32_t crystal, uint32_t frequency)
* 	static void system_init(void)
*
* available interrupt handlers:
******************************************************************************/

/*
+=============================================================================+
| includes
+=============================================================================+
*/


#include "config.h"
#include "init.h"
#include "systicks.h"

#include "serial.h"


/*------------------------------------------------------------------------*//**
* \brief main code block
* \details Call some static initialization functions and blink the led with
* frequency defined via count_max variable.
*//*-------------------------------------------------------------------------*/
#include "hdr/hdr_gpio_masked_access.h"
#define LED_GPIO							LPC_GPIO1	///< GPIO port to which the LED is connected
#define LED_pin								8			///< pin number of the LED
#define LED									(1 << LED_pin)
/// "variable" to manipulate the pin directly via GPIO masked access
#define LED_gma								gpio_masked_access_t GPIO_MASKED_ACCESS(LED_GPIO, LED_pin)

int main(void) {
	volatile uint32_t count, count_max = 1000000;	// with core frequency 48MHz this gives ~1.5Hz blinking frequency

	system_init();							// initialize other necessary elements

	LED_GPIO->DIR |= LED;					// set the direction of the LED pin to output

	initUART();

	printString("Boldly going :)\r\n");

	while (1)
	{
		for (count = 0; count < count_max; count++);	// delay
		LED_gma = LED;						// instead of LED_GPIO->DATA |= LED;
		printString("1...\r\n");
		for (count = 0; count < count_max; count++);	// delay
		LED_gma = 0;						// instead of LED_GPIO->DATA &= ~LED;
		printString("2...\r\n");
	}
}


/*
+=============================================================================+
| ISRs
+=============================================================================+
*/


