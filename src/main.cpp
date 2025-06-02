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

#include "car.h"


#include "WiFiMulti.h"
#include "Audio.h"
/*Set to your screen resolution and rotation*/
#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_90

#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
uint8_t data[3];
 
#define I2S_DOUT      45
#define I2S_BCLK      46
#define I2S_LRC       10
#define I2S_DIN    9
Audio audio;
WiFiMulti wifiMulti;
 
// config your wifi
String ssid =     "TP-LINK_F37E";
String password = "meiyoumima";
 


SET_LOOP_TASK_STACK_SIZE(100*1024);  
 
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
 #if 1
    HAL::HAL_Init();
    lv_init();
    lv_tick_set_cb(my_tick);
 
    lv_display_t * disp;
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);
    lv_port_indev_init();

    App_Init();
#endif
 
    lvgl_i2c_read(I2C_NUM_0,0x0d, 0x0d, data, 1);
    printf("qmi5883 id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x6a, 0x0f, data, 1);
    printf("LSM6DS3 id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x15, 0xA7, data, 1);
    printf("ctp id : 0x%x\r\n",data[0]);
    lvgl_i2c_read(I2C_NUM_0,0x22, 0x01, data, 1);
    printf("pd id : 0x%x\r\n",data[0]);
    
    lvgl_i2c_read(I2C_NUM_0,0x60,0x00, data, 1);
    printf("pcf id1 : 0x%x\r\n",data[0]);

    lvgl_i2c_read(I2C_NUM_0,0x40, 0xff, data, 1);
    printf("ina226 id : 0x%x\r\n",data[0]);

 
 #if 0
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(ssid.c_str(), password.c_str());
    wifiMulti.run();
    while(WiFi.status() != WL_CONNECTED){
        WiFi.disconnect(true);
        wifiMulti.run();
    }
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(12); // 0...21
    delay(1000);
     printf("Connected. Starting MP3...\r\n");
    audio.connecttohost("http://192.168.0.106:50000/gradio_api/stream/5o9idoedw5c/1964809397456/21/playlist-file"); 
 #endif                       

    
 #if 0 // 初始化 Lottie 动画
    lv_obj_t * lottie_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(lottie_screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(lottie_screen, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(lottie_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_disp_load_scr(lottie_screen);


    // 初始化 Lottie 动画
    lv_obj_t * lottie_obj = lv_rlottie_create_from_raw(lottie_screen, 200, 200, (const char*)car);
    lv_obj_center(lottie_obj);
    
    printf("Arduino Stack was set to %d bytes", getArduinoLoopTaskStackSize());
    printf("\nSetup() - Free Stack Space: %d", uxTaskGetStackHighWaterMark(NULL));
#endif
}

void loop()
{
    lv_timer_handler();  
    //audio.loop();
    vTaskDelay(1);
    
}

void audio_info(const char *info){
     printf("%s\r\n",info);
}
void audio_id3data(const char *info){  //id3 metadata
    printf("%s\r\n",info);
}
void audio_eof_mp3(const char *info){  //end of file
    printf("%s\r\n",info);
}
void audio_showstation(const char *info){
    printf("%s\r\n",info);
}
void audio_showstreamtitle(const char *info){
   printf("%s\r\n",info);
}
void audio_bitrate(const char *info){
   printf("%s\r\n",info);
}
void audio_commercial(const char *info){  //duration in sec
    printf("%s\r\n",info);
}
void audio_icyurl(const char *info){  //homepage
    printf("%s\r\n",info);
}
void audio_lasthost(const char *info){  //stream URL played
    printf("%s\r\n",info);

}