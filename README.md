# keyboard_demo
keyboard demo on stm32f103 


A simple demonstration project for stm32f103 "blue pill" evaluation board and 7-pin 12-key keyboard. FreeRTOS is used 
MCU outputs a key(s) pressed  distinguishing a hit events in 2 groups: short and long(more than one second) pressed keys
Works only under debugger with stLink connected due a semihosting usage.
Led blinks in a separate thread with 1 second frequency
