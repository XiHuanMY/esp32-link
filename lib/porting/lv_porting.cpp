#include <Arduino.h>
#include <Wire.h> 
#include "i2c_manager.h"  
#include "lvgl.h"
#include "lv_porting.h"
#include  <rk816.h> 
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
 
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
 
void lv_porting_init(void)
{
    i2c_master_init();
    rk816_init_power();
    delay(1000); // 等待电源稳定

    lv_init();
    
    lv_display_t * disp;
    disp = lv_tft_espi_create(TFT_WIDTH, TFT_HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
 
}
