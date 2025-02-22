/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/integration/framework/arduino.html  */

#include <lvgl.h>
#include "i2c_manager.h"

#include "Resource/ResourcePool.h"
#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

#include "APP.h"
#include "Common/HAL/HAL.h"
#include "lvgl_indev_port.h"
 
 /*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
  *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
  *Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
  *as the examples and demos are now part of the main LVGL library. */
 
 //#include <examples/lv_examples.h>
 //#include <demos/lv_demos.h>

 /*Set to your screen resolution and rotation*/
 #define TFT_HOR_RES   240
 #define TFT_VER_RES   320
 #define TFT_ROTATION  LV_DISPLAY_ROTATION_90
 
 /*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
 #define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
 uint32_t draw_buf[DRAW_BUF_SIZE / 4];
 uint8_t data[2];
  
 /*use Arduinos millis() as tick source*/
 static uint32_t my_tick(void)
 {
     return millis();
 } 
 void setup()
 {
    Serial.begin( 115200 ); 
    delay(3000);
    HAL::HAL_Init();


    lv_init();
    /*Set a tick source so that LVGL will know how much time elapsed. */
    lv_tick_set_cb(my_tick);
 
    lv_display_t * disp;
    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);

     
    lv_port_indev_init();

    Serial.println( "Setup done" );



    App_Init();
  
    lvgl_i2c_read(I2C_NUM_0,0x0d, 0x0d, data, 1);
    printf("qmi5883 id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x6a, 0x0f, data, 1);
    printf("LSM6DS3 id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x15, 0xA7, data, 1);
    printf("ctp id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x22, 0x01, data, 1);
    printf("pd id : 0x%x\r\n",data[0]);
 }
 
 void loop()
 {
     lv_timer_handler(); /* let the GUI do its work */
     delay(5); /* let this time pass */
 }
 