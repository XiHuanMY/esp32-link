/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/integration/framework/arduino.html  */

#include <lvgl.h>
#include "i2c_manager.h"

#include "Resource/ResourcePool.h"
 #if LV_USE_TFT_ESPI
 #include <TFT_eSPI.h>
 #endif
 
 #include "APP.h"
#include "lvgl_indev_port.h"
 
 /*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
  *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
  *Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
  *as the examples and demos are now part of the main LVGL library. */
 
 //#include <examples/lv_examples.h>
 //#include <demos/lv_demos.h>

 /*Set to your screen resolution and rotation*/
 #define TFT_HOR_RES   240
 #define TFT_VER_RES   280
 #define TFT_ROTATION  LV_DISPLAY_ROTATION_90
 
 /*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
 #define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
 uint32_t draw_buf[DRAW_BUF_SIZE / 4];
 uint8_t data[2];
 #if LV_USE_LOG != 0
 void my_print( lv_log_level_t level, const char * buf )
 {
     LV_UNUSED(level);
     Serial.println(buf);
     Serial.flush();
 }
 #endif
 
 /* LVGL calls it when a rendered image needs to copied to the display*/
 void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
 {
     /*Copy `px map` to the `area`*/
 
     /*For example ("my_..." functions needs to be implemented by you)
     uint32_t w = lv_area_get_width(area);
     uint32_t h = lv_area_get_height(area);
 
     my_set_window(area->x1, area->y1, w, h);
     my_draw_bitmaps(px_map, w * h);
      */
 
     /*Call it to tell LVGL you are ready*/
     lv_display_flush_ready(disp);
 }
 
 /*Read the touchpad*/
 void my_touchpad_read( lv_indev_t * indev, lv_indev_data_t * data )
 {
     /*For example  ("my_..." functions needs to be implemented by you)
     int32_t x, y;
     bool touched = my_get_touch( &x, &y );
 
     if(!touched) {
         data->state = LV_INDEV_STATE_RELEASED;
     } else {
         data->state = LV_INDEV_STATE_PRESSED;
 
         data->point.x = x;
         data->point.y = y;
     }
      */
 }
 
 /*use Arduinos millis() as tick source*/
 static uint32_t my_tick(void)
 {
     return millis();
 }
 static void anim_x_cb(void * var, int32_t v)
{
    lv_obj_set_x((lv_obj_t *)var, v);
}
 
 void setup()
 {
    Serial.begin( 115200 ); 
    delay(3000);
    //App_Init();


    //lvgl_i2c_locking(lvgl_i2c_mutex());
    lv_init();
    /*Set a tick source so that LVGL will know how much time elapsed. */
    lv_tick_set_cb(my_tick);
    /* register print function for debugging */
 #if LV_USE_LOG != 0
     lv_log_register_print_cb( my_print );
 #endif
 
    



    lv_display_t * disp;
    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);

     
    lv_port_indev_init();
    Serial.println( "Setup done" );
    App_Init();
  
      
        //lv_anim_timeline_add(at, atw->start_time, &a);
       // ui.labelLogo = label;

        //ui.anim_timeline = lv_anim_timeline_create();
/*
    #define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

       lv_anim_timeline_wrapper_t wrapper[] =
            {
                ANIM_DEF(0, ui.cont, width, 0, lv_obj_get_style_width(ui.cont, 0)),
                ANIM_DEF(500, ui.labelLogo, y, lv_obj_get_style_height(ui.cont, 0), lv_obj_get_y(ui.labelLogo)),
                LV_ANIM_TIMELINE_WRAPPER_END};

        lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);

 lv_screen_active()

*/
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
 