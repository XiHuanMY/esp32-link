#include <Arduino.h>
#include <Wire.h> 
#include "i2c_manager.h"  
#include "lvgl.h"
#include "lv_porting.h"
#include  <rk816.h> 
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "lvgl_disp_port.hpp"
#include "lvgl_indev_port.h"

uint32_t draw_buf[DRAW_BUF_SIZE / 4];
 
void lv_porting_init(void)
{
    i2c_master_init();
    rk816_init_power();
    delay(1000); // 等待电源稳定
    printf("aaaaaaa\r\n");
    lv_init();
    
    lv_port_disp_init();
    printf("aaaaaaa\r\n");
    lv_port_indev_init();
    printf("aaaaaaa\r\n");
 
}
