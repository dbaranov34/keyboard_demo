/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "keyboard.h"
#include "led.h"
#include "responder.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId keyboardTaskHandle;
osThreadId ledTaskHandle;


/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/

/*
 * Polls a keypad and ouptuts keys pressed
 * */
void StartKeyboardTask(void const * argument);

/*
 * Indicates that we are on (diode blink)
 * */
void StartLedTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* Create the timer(s) */
	/* definition and creation of keyHoldedTimer */

	/* USER CODE BEGIN RTOS_TIMERS */

	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* Create the thread(s) */
	/* definition and creation of keyboardTask */
	osThreadDef(keyboardTask, StartKeyboardTask, osPriorityNormal, 0, 256);
	keyboardTaskHandle = osThreadCreate(osThread(keyboardTask), NULL);

	/* definition and creation of ledTask */
	osThreadDef(ledTask, StartLedTask, osPriorityIdle, 0, 128);
	ledTaskHandle = osThreadCreate(osThread(ledTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* Create the queue(s) */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */
}

/* StartKeyboardTask function */
void StartKeyboardTask(void const * argument) {

	/* USER CODE BEGIN StartKeyboardTask */
	char kb_string[KEYBOARD_MAX_MULTITOUCH];
	char prev_string[KEYBOARD_MAX_MULTITOUCH];
	static KEYS_PRESSED keys = { 0, 0, 0, 0 };
	uint32_t tick;
	/* Infinite loop */
	for (;;) {

		strcpy(prev_string, kb_string);
		KeyboardPoll(kb_string);

		//if we have non-empty string during debounce time
		if (0 != strcmp("", kb_string)) {
			//we`ve detected pressing!
			tick = HAL_GetTick();
			do {
				//now wait for release
				osDelay(KEYBOARD_BOUNCE_TIME / 2);
				strcpy(prev_string, kb_string);
				KeyboardPoll(kb_string);
			} while (0 == strcmp(kb_string, prev_string));
			//YEAH YEAH. IF WE WILL HOLD A BUTTON EXACTLY maxuint32_t/1000 seconds we`ll make a mistake...
			//This device is not supposed to be working more than a hour
			tick = HAL_GetTick() - tick;
			if (tick > KEYBOARD_BOUNCE_TIME) {
				keys.key_1 = (char) prev_string[0];
				keys.key_2 = (char) prev_string[1];
				if (tick > KEYBOARD_LONG_PRESSED_CRITERION) {
					keys.presstype = LONG_PRESSED;
				} else {
					keys.presstype = SHORT_PRESSED;
				}
			}

			LedOn();
			if (keys.presstype == SHORT_PRESSED) {

				if (0 == keys.key_2) {
					single_key_pressed(keys.key_1);
				} else {
					double_key_pressed(keys.key_1, keys.key_2);
				}
			}

			else {
				if (0 == keys.key_2) {
					single_key_long_pressed(keys.key_1);
				} else {
					double_key_long_pressed(keys.key_1, keys.key_2);
				}
			}
		}
//now analyse what we have;y

//printf(strcat(kb_string, "\n"));
		osDelay(KEYBOARD_BOUNCE_TIME);

	}
	/* USER CODE END StartKeyboardTask */
}

/* StartLedTask function */
void StartLedTask(void const * argument) {
	/* USER CODE BEGIN StartLedTask */
	/* Infinite loop */
	for (;;) {
		LedOn();
		osDelay(100);
		LedOff();
		osDelay(900);
	}
	/* USER CODE END StartLedTask */
}

/* KeyHoldedTimerCallback function */


/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
