/*
 * keyboard.h
 *
 *  Created on: 25 мая 2018 г.
 *      Author: Dbaranov
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "stm32f1xx_hal.h"
/*
 * Keyboard GPIO initializer.
 * Writes 1 to COL_* pins
 */

#define KEYBOARD_ROWS 4
#define KEYBOARD_COLUMNS 3
#define KEYBOARD_MAX_MULTITOUCH 3
#define KEYBOARD_BOUNCE_TIME 20 //measuren in os_ticks (1ms by defaults)

void KeyboardPoll(char* kb_string);

#endif /* KEYBOARD_H_ */
