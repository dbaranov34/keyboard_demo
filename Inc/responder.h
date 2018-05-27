/*
 * responder.h
 *
 *  Created on: 27 мая 2018 г.
 *      Author: Dbaranov
 */

#ifndef RESPONDER_H_
#define RESPONDER_H_

#include <stdio.h>

#define OUTPUT_LENGTH 64

void single_key_pressed(char key);
void double_key_pressed(char key, char key2);
void single_key_long_pressed(char key);
void double_key_long_pressed(char key, char key2);

#endif /* RESPONDER_H_ */
