#include <Arduino.h>
#include <Wire.h> // 添加Wire库
#include "lv_porting.h"
 

void setup() {
  Serial.begin(115200);
  delay(3000);
  lv_porting_init();
}
 
void loop() { 
  delay(10);
}
 