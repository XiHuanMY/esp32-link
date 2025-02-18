#include "keypad.h"
#include "esp_log.h"

#include "driver/gpio.h"
 
 void keypad_driver_init(void)
 {
    gpio_pad_select_gpio(KEYPAD_DOWN);
    gpio_pad_select_gpio(KEYPAD_UP);
    gpio_pad_select_gpio(KEYPAD_ENTER);
    

    gpio_pad_pullup(KEYPAD_DOWN);
    gpio_pad_pullup(KEYPAD_UP);
    gpio_pad_pullup(KEYPAD_ENTER);
    

    gpio_set_direction(KEYPAD_DOWN, GPIO_MODE_INPUT);
    gpio_set_direction(KEYPAD_UP, GPIO_MODE_INPUT);
    gpio_set_direction(KEYPAD_ENTER, GPIO_MODE_INPUT);
 }
uint32_t keypad_get_key(void)
{
    /*Your code comes here*/
     if(gpio_get_level(KEYPAD_UP)==0)
    {
        return 1;
    }
    else if (gpio_get_level(KEYPAD_DOWN)==0)
    {
        return 2;  
    }
     else if (gpio_get_level(KEYPAD_ENTER)==0)
    {
        return 3; 
    }
   
    return 0;
}


