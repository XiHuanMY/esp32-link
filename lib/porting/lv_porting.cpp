#include <Arduino.h>
#include <Wire.h> // 添加Wire库
#include "i2c_manager.h"  
#include "lvgl.h"
#include "lv_porting.h"
#include  <rk816.h> 

void lv_porting_init(void)
{
    i2c_master_init();
    rk816_init_power();

}
