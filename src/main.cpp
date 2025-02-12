#include <Arduino.h>
#include <Wire.h> // 添加Wire库
#include "lv_porting.h"
#include <lvgl.h>
#include "App.h"

void setup() {
    Serial.begin(115200);
    delay(3000);
    lv_porting_init();
    delay(3000);
    App_Init();
}
 
void loop() { 
    lv_task_handler();
    delay(10);
}
 