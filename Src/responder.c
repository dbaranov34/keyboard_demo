/*
 * responder.c
 *
 *  Created on: 27 мая 2018 г.
 *      Author: Dbaranov
 */

#include "responder.h"
static char outstring[OUTPUT_LENGTH];

void single_key_pressed(char key);
void double_key_pressed(char key, char key2);
void single_key_long_pressed(char key);
void double_key_long_pressed(char key, char key2);

void single_key_pressed(char key) {
	memset(outstring, 0, OUTPUT_LENGTH);
	sprintf(outstring, "Single_key_pressed. Key: %c.\n", key);
	printf(outstring);

}
void double_key_pressed(char key, char key2) {
	memset(outstring, 0, OUTPUT_LENGTH);
	sprintf(outstring, "Two keys pressed. Keys: %c, %c.\n", key, key2);
	printf(outstring);
}

void single_key_long_pressed(char key) {
	memset(outstring, 0, OUTPUT_LENGTH);
	sprintf(outstring, "Single_key_pressed long. Key: %c.\n", key);
	printf(outstring);
}
void double_key_long_pressed(char key, char key2) {
	memset(outstring, 0, OUTPUT_LENGTH);
	sprintf(outstring, "Two keys pressed long. Keys: %c, %c.\n", key, key2);
	printf(outstring);
}
