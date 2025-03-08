#include <cstdio>
#include "HAL.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "rk816.h"
#include <time.h> 
#include "i2c_manager.h"
#define TAG "HOME"
TaskHandle_t home_task_handle = NULL;
struct tm timeinfo; 
extern "C"
{

    static void home_task(void *pvParameter)
    {
        ESP_LOGI(TAG, "home task on \r\n");
         int sec, min, hour, day,  month, year, week;
        uint8_t  statue[2];
        //gpio_set_direction((gpio_num_t)45, GPIO_MODE_OUTPUT);
        //gpio_set_level((gpio_num_t)45, 0);
        while (1)
        {  
            rk816_rtc_get_time(&sec, &min, &hour, &day, &month, &year, &week);
            printf("get time sec %d, min %d, hour %d, day %d, month %d, year %d, week %d\r\n", sec, min, hour, day, month, year, week);
            vTaskDelay(1000);
        }
    }
}

void HAL::Home_Init(Home_Info_t *test_info)
{
     
    xTaskCreate(home_task, "home_task", 1024 * 8, NULL, 8, &home_task_handle);
}
 
 
void HAL::Home_Update(Home_Info_t *test_info)
{
    switch (test_info->home_cmd)
    {
        case Ts_UPDATE:
        {
            //data1 = test_info->data1;
            break;
        }
        default:
            break;

    }
}
 