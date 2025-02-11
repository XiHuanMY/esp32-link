#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include "AudioFileSourceSPIFFS.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"
// Wi-Fi 设置
#include <Wire.h> // 添加Wire库
#include "i2c_manager.h"  
#include  <rk816.h> 
#include  <ina226.h> 
#include  <ws2812.h> 
#include "CST816T.h"
#include <lvgl.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "lv_porting.h"
 
 

#define TFT_DC    14
#define TFT_RST   13
#define TFT_MOSI  11   // for hardware SPI data pin (all of available pins)
#define TFT_SCLK 12   // for hardware SPI sclk pin (all of available pins)
#define TFT_BL   17
#define TFT_CS -1



// 创建音频对象
AudioGeneratorWAV *wav;
AudioFileSourceSPIFFS *file;
AudioOutputI2S *out;
 
INA226_WE *ina226;
CST816T cst816t(18, 21, 15, NOT_A_PIN); 

TouchInfos tp;
#define TFT_GREY 0x5AEB // New colour
 
#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

TFT_eSPI tft = TFT_eSPI();  // Invoke library
LiteLED myLED( LED_TYPE, LED_TYPE_IS_RGBW );
 
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

void my_touchpad_read( lv_indev_t * indev, lv_indev_data_t * data )
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
static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        printf("Clicked\r\n");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        printf("Toggled\r\n");
    }
}
void setup() {

    uint8_t id = 0x0;
  // 初始化串口，用于调试
  Serial.begin(115200);
  delay(3000);
  lv_porting_init();
#if 0
  Serial.print("aaaaaaaa\r\n");
 if(LittleFS.begin()){
    
    Serial.print("\r\nlittleFS 系统打开成功\r\n");
    File root =LittleFS.open("/","r");
 
    File file = root.openNextFile();
    while (file)
    {
       Serial.println(file.name());
      file = root.openNextFile();
    }
  }
  else{
     Serial.print("littleFS 系统打开失败，请进行检查");
    }
  //  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
   
    // Init Display

    //cst816t.begin(); 

  // 初始化I2S输出
  out = new AudioOutputI2S();
  out->SetPinout(46, 10, 45);
  out->begin();
 
    i2c_master_init();
    rk816_init_power();

    ina226->init();
    tft.init();
     tft.setRotation(2);
     String LVGL_Arduino = "Hello Arduino! ";
     LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  

     lv_init();
     lv_tick_set_cb(my_tick);
     lv_display_t * disp;
     
    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_WIDTH, TFT_HEIGHT, draw_buf, sizeof(draw_buf));
     lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    lv_indev_set_read_cb(indev, my_touchpad_read);
 
    lv_obj_t * btn1 = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn1, 200, 100);  
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

    lv_obj_t * label = lv_label_create(btn1);
    lv_label_set_text(label, "RGB");
    lv_obj_center(label);







    i2c_manager_read(I2C_MASTER_NUM,0x0d, 0x0d, &id, 1);
    printf("qmi5883 id : 0x%x\r\n",id);

    i2c_manager_only_read(I2C_MASTER_NUM,0X20, &id, 1);
    printf("fpc85741 id : 0x%x\r\n",id);
    id = 0xbe;
    i2c_manager_only_write(I2C_MASTER_NUM,0X20,&id,1);
    i2c_manager_only_read(I2C_MASTER_NUM,0X20, &id, 1); 
    printf("fpc85742 id : 0x%x\r\n",id);
    
    i2c_manager_read(I2C_MASTER_NUM,0x6a, 0x0f, &id, 1);
    printf("LSM6DS3 id : 0x%x\r\n",id);

    i2c_manager_read(I2C_MASTER_NUM,0x15, 0xA7, &id, 1);
    printf("ctp id : 0x%x\r\n",id);
 
 
    i2c_manager_read(I2C_MASTER_NUM,0x22, 0x01, &id, 1);
    printf("pd id : 0x%x\r\n",id);
 
 
    myLED.begin( LED_GPIO, 1 );         // initialze the myLED object. Here we have 1 LED attached to the LED_GPIO pin 
    myLED.brightness( LED_BRIGHT );     // set the LED photon intensity level
    myLED.setPixel( 0, L_GREEN, 1 );    // set the LED colour and show it
    delay( 2000 );
    myLED.brightness( 0, 1 );           // turn the LED off
#endif
  // 从URL获取MP3文件并播放
  //file = new AudioFileSourceSPIFFS("/1.wav");
 // wav = new AudioGeneratorWAV();
  //wav->begin(file, out);
}
 
void loop() {
  // 播放MP3文件
 /*if (wav->isRunning()) {
    wav->loop();
  } else {
    wav->stop();
    Serial.println("Playback stopped");
    delay(1000);
  }
  */ 
 
 //lv_timer_handler(); /* let the GUI do its work */
  
 //myLED.brightness( 0, 1 );  
  delay(10);
 //myLED.brightness( 30, 1 );  
/* tft.fillScreen(TFT_GREY);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
  // We can now plot text on screen using the "print" class
  tft.println("Hello World!");
  
  // Set the font colour to be yellow with no background, set to font 7
  tft.setTextColor(TFT_YELLOW); tft.setTextFont(7);
  tft.println(1234.56);
  */
}
 