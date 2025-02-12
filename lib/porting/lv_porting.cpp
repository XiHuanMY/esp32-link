#include <Arduino.h>
#include <Wire.h> 
#include "i2c_manager.h"  
#include "lvgl.h"
#include "lv_porting.h"
#include  <rk816.h> 
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>


#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

static void my_touchpad_read( lv_indev_t * indev, lv_indev_data_t * data )
{
    uint8_t touchData[7];
    int32_t x, y;
    i2c_manager_read(I2C_MASTER_NUM,0x15, 0x00, touchData, 7);
    if(touchData[2] == 0x00) {
        data->state = LV_INDEV_STATE_RELEASED;
    } else {
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = ((touchData[3]&0x0f) << 8) | touchData[4];
        data->point.y = ((touchData[5]&0x0f) << 8) | touchData[6];
        printf("CST816T (%d,%d, %4d, %4d)\n", touchData[2],touchData[1],data->point.x, data->point.y); 
    }
}
static uint32_t my_tick(void)
{
    return millis();
}
void lv_porting_init(void)
{
    i2c_master_init();
    rk816_init_power();
    delay(1000); // 等待电源稳定
    
    lv_init();
    lv_tick_set_cb(my_tick);
    lv_display_t * disp;

    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_WIDTH, TFT_HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    lv_indev_set_read_cb(indev, my_touchpad_read);

    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Loading...");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

}
