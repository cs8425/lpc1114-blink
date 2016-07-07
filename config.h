/** \file config.h
 * \brief Basic configuration of the project
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-08
 */

/******************************************************************************
* project: lpc1114_blink_led
* chip: LPC1114
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
******************************************************************************/

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdint.h>

#include "LPC11xx.h"
#include "system_LPC11xx.h"
#include "cmsis.h"

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

#define CRYSTAL								12000000	///< quartz crystal resonator which is connected to the chip
#define FREQUENCY							48000000	///< desired target frequency of the core


/*
+=============================================================================+
| strange variables
+=============================================================================+
*/

/*
+=============================================================================+
| global variables
+=============================================================================+
*/

/*
+=============================================================================+
| global functions' declarations
+=============================================================================+
*/

#endif
