/*
 * keyboard.h
 *
 *  Created on: 25 ��� 2018 �.
 *      Author: Dbaranov
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "stm32f1xx_hal.h"


#define KEYBOARD_ROWS 4 					//y-dimension of the ketboard
#define KEYBOARD_COLUMNS 3 					//x-dimension of the ketboard
#define KEYBOARD_MAX_MULTITOUCH 2			//maxNum of keys could be legally pressed
#define KEYBOARD_BOUNCE_TIME 30				// measured in os_ticks (1ms by defaults)
#define KEYBOARD_LONG_PRESSED_CRITERION 1000// measured in miliseconds. Do not forget  to call once SystemCoreClockUpdate() somewhere before

#define LONG_PRESSED 1
#define SHORT_PRESSED 0

typedef struct keys_pressed{
	char key_1;
	char key_2;
	uint8_t presstype;
	uint8_t align_1;
} KEYS_PRESSED;

/*
 * Keyboard poller.
 * Returns a ptr to string with keys pressed.
 * String must be long enough.
 * Unsafe funciton!
 *
 */
void KeyboardPoll(char* kb_string);

#endif /* KEYBOARD_H_ */
