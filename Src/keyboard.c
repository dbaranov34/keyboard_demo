#include "keyboard.h"
#include "cmsis_os.h"


#ifndef STM32F103xB
#warning "check type of clm_pins[] and row_pins[]  according to MCU architecture"
#endif

//pinmap
const uint16_t clm_pins[3] = { CLM_1_Pin, CLM_2_Pin, CLM_3_Pin };
const uint16_t row_pins[4] = { ROW_1_Pin, ROW_2_Pin, ROW_3_Pin, ROW_4_Pin };
//charmap
const char kb_symbols[KEYBOARD_ROWS][KEYBOARD_COLUMNS] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' }, { '*', '0', '#' } };




void KeyboardPoll(char* kb_out) {

	char c;
	uint8_t num_keys_pressed = 0;
	//reset output string
	memset(kb_out, 0, KEYBOARD_MAX_MULTITOUCH);

	//power-up column lines
	for (uint8_t col = 0; col < KEYBOARD_COLUMNS; col++) {
		HAL_GPIO_WritePin(CLM_GPIO_Port, (uint16_t) clm_pins[col], SET);
		//polling rows
		for (uint8_t row = 0; row < KEYBOARD_ROWS; row++) {
			//if we hit a key
			if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ROW_GPIO_Port, (uint16_t) row_pins[row])) {
				//match the symbol
				c = (char) kb_symbols[row][col];
				//write in output
				kb_out[num_keys_pressed] = c;
				//inc number of keys pressed
				num_keys_pressed++;
				//if too much keys pressed
				if (num_keys_pressed > KEYBOARD_MAX_MULTITOUCH) {
					//keyboard multitouch limit erases output
					memset(kb_out, 0, KEYBOARD_MAX_MULTITOUCH);
					kb_out[0] = '\0';
					return;
				}
			}
		}
		//power-down the column
		HAL_GPIO_WritePin(CLM_GPIO_Port, clm_pins[col], RESET);
	}
	return;
}
