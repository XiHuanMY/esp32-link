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
uint16_t data1 = 0;
extern "C"
{

    static void test_task(void *pvParameter)
    {
        ESP_LOGI(TAG, "test task on \r\n");
        //gpio_set_direction((gpio_num_t)45, GPIO_MODE_OUTPUT);
        //gpio_set_level((gpio_num_t)45, 0);
        while (1)
        {
            /* code */
            printf("data : %d\r\n", data1);
            vTaskDelay(1000);
        }
    }
}

void HAL::Test_Init(Test_Info_t *test_info)
{
    data1 = test_info->data1;
    xTaskCreate(test_task, "test_task", 1024 * 8, NULL, 8, &test_task_handle);
}
 
 
void HAL::Test_Update(Test_Info_t *test_info)
{
    switch (test_info->test_cmd)
    {
        case Ts_UPDATE:
        {
            data1 = test_info->data1;
            break;
        }
        default:
            break;

    }
}
 