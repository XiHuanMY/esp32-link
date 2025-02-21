#include <cstdio>
#include "HAL.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"

#define TAG "TEST"
TaskHandle_t test_task_handle = NULL;
 
extern "C"
{

    static void test_task(void *pvParameter)
    {
        ESP_LOGI(TAG, "test task on \r\n");
        gpio_set_direction((gpio_num_t)45, GPIO_MODE_OUTPUT);
        gpio_set_level((gpio_num_t)45, 0);

 
        while (1)
        {
            /* code */
 
            vTaskDelay(5);
        }
        }
}

void HAL::Test_Init()
{
    ESP_LOGI(TAG, "power_pd_c init \r\n");
    xTaskCreate(test_task, "test_task", 1024 * 8, NULL, 8, &test_task_handle);
}
 
 
void HAL::Test_Update(Test_Info_t *test_info)
{
  
}
 