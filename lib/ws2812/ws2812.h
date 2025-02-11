/******************************************************************************
 *
 * This is a library for the INA226 Current and Power Sensor Module
 *
 * You'll find several example sketches which should enable you to use the library. 
 *
 * You are free to use it, change it or build on it. In case you like it, it would
 * be cool if you give it a star.
 *
 * If you find bugs, please inform me!
 * 
 * Written by Wolfgang (Wolle) Ewald
 * https://wolles-elektronikkiste.de/en/ina226-current-and-power-sensor (English)
 * https://wolles-elektronikkiste.de/ina226 (German)
 *
 * 
 ******************************************************************************/

#ifndef WS2812_H_
#define WS2812_H_

#include <stdint.h>
#include <stdbool.h>

#include <LiteLED.h>
 
#define LED_TYPE        LED_STRIP_WS2812

#define LED_TYPE_IS_RGBW 0   // if the LED is an RGBW type, change the 0 to 1
#define LED_GPIO 33     // change this number to be the GPIO pin connected to the LED
#define LED_BRIGHT 30   // sets how bright the LED is. O is off; 255 is burn your eyeballs out (not recommended)

static const crgb_t L_RED = 0xff0000;
static const crgb_t L_GREEN = 0x00ff00;
static const crgb_t L_BLUE = 0x0000ff;
static const crgb_t L_WHITE = 0xe0e0e0;


#endif

