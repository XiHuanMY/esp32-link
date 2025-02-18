#ifndef __MY_KEYPAD_H
#define __MY_KEYPAD_H
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

 

#define KEYPAD_DOWN 38               
#define KEYPAD_UP 39                
#define KEYPAD_ENTER 0              
 

void keypad_driver_init(void);
uint32_t keypad_get_key(void);

#endif