#include <Arduino.h>
#include <lvgl.h>
#include "i2c_manager.h"
#include "Resource/ResourcePool.h"

#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

#include "APP.h"
#include "Common/HAL/HAL.h"
#include "lvgl_indev_port.h"
#include "rk816.h"
/*Set to your screen resolution and rotation*/
#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_90

#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
uint8_t data[3];
static uint32_t my_tick(void)
{
    return millis();
} 
void setup()
{
    Serial.begin( 115200 ); 
    delay(5000);
    rk816_init_power();
    delay(2000);
    HAL::HAL_Init();
    lv_init();
    lv_tick_set_cb(my_tick);
 
    lv_display_t * disp;
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);
    lv_port_indev_init();

    App_Init();


    lvgl_i2c_read(I2C_NUM_0,0x0d, 0x0d, data, 1);
    printf("qmi5883 id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x6a, 0x0f, data, 1);
    printf("LSM6DS3 id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x15, 0xA7, data, 1);
    printf("ctp id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x22, 0x01, data, 1);
    printf("pd id : 0x%x\r\n",data[0]);
    
    uint8_t val =0x40;
    lvgl_i2c_read(I2C_NUM_0,0x60,0.00, data, 1);
    printf("pcf id1 : 0x%x\r\n",data[0]);

    lvgl_i2c_read(I2C_NUM_0,0x40, 0xff, data, 1);
    printf("ina226 id : 0x%x\r\n",data[0]);
}

void loop()
{
    lv_timer_handler();  
    delay(5);  
}
