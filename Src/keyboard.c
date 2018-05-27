#include "keyboard.h"

const char kb_symbols[KEYBOARD_ROWS][KEYBOARD_COLUMNS] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' }, { '*', '0', '#' } };

#ifndef STM32F103xB
#warning "check type of clm_pins[] and row_pins[]  according to MCU architecture"
#endif

const uint16_t clm_pins[3] = { CLM_1_Pin, CLM_2_Pin, CLM_3_Pin };
const uint16_t row_pins[4] = { ROW_1_Pin, ROW_2_Pin, ROW_3_Pin, ROW_4_Pin };

int a;

void KeyboardInit(void) {
	HAL_GPIO_WritePin(CLM_GPIO_Port, CLM_1_Pin, SET);
	HAL_GPIO_WritePin(CLM_GPIO_Port, CLM_2_Pin, SET);
	HAL_GPIO_WritePin(CLM_GPIO_Port, CLM_3_Pin, SET);
}

void KeyboardPoll(char* kb_out) {
	char c;
	char *pChar = &c;
	uint8_t num_keys_pressed = 0;
	kb_out[0] = '\0';
	for (uint8_t col = 0; col < KEYBOARD_COLUMNS; col++) {
		HAL_GPIO_WritePin(CLM_GPIO_Port, (uint16_t) clm_pins[col], SET);
		for (uint8_t row = 0; row < KEYBOARD_ROWS; row++) {
			if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ROW_GPIO_Port, (uint16_t) row_pins[row])) {
				num_keys_pressed++;
				c = (char) kb_symbols[row][col];
				strcat(kb_out, pChar);
				if (num_keys_pressed > KEYBOARD_MAX_MULTITOUCH) {
					kb_out[0] = '\0';
					return;
				}
			}
		}
		HAL_GPIO_WritePin(CLM_GPIO_Port, clm_pins[col], RESET);
	}
	return;
}
