
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/pcnt.h"
#include "driver/gpio.h"
#include "driver/rmt.h"
#include "esp_log.h"
#include "driver/pcnt.h"
#include "driver/gpio.h"
#include "frequency_count.h"
#include "esp_timer.h"

#define TAG "frequency_counter"

#define PULSE_GPIO_INPUT 1
#define PULSE_PCNT_HIGH_LIMIT 32000
#define PULSE_SAMPLE_TIME (1000*1000)
static int unit = PCNT_UNIT_0;
 

esp_timer_handle_t oneshot_timer;
volatile uint32_t pulse_count=0;
volatile bool timer_mes = false;
 static void pcnt_init(void)
{
        /* Prepare configuration for the PCNT unit */
    pcnt_config_t pcnt_config = {
        .pulse_gpio_num = PULSE_GPIO_INPUT,
        .ctrl_gpio_num = -1,
        .channel = PCNT_CHANNEL_0,
        .unit = unit,
        .pos_mode = PCNT_COUNT_DEC,
        .neg_mode = PCNT_COUNT_INC,
        .lctrl_mode = PCNT_MODE_REVERSE,
        .hctrl_mode = PCNT_MODE_KEEP,
        .counter_h_lim = PULSE_PCNT_HIGH_LIMIT,
        .counter_l_lim = 0,
    };

    /* Initialize PCNT unit */
    pcnt_unit_config(&pcnt_config);

    /* Configure and enable the input filter */
    pcnt_set_filter_value(unit, 1000);
    pcnt_filter_enable(unit);

    /* Initialize PCNT's counter */
    pcnt_counter_pause(unit);
    pcnt_counter_clear(unit);
    printf("pcnt_init OK \r\n");
}

static void oneshot_timer_callback(void *arg)
{
    esp_timer_handle_t periodic_timer_handle = (esp_timer_handle_t)arg;
    timer_mes = false;
    pcnt_counter_pause(unit);
    uint16_t pcount;
    pcnt_get_counter_value(unit, &pcount);
    pulse_count += pcount;
}

static void timer_init(uint32_t time)
{
    const esp_timer_create_args_t oneshot_timer_args = {
        .callback = &oneshot_timer_callback,
        /* argument specified here will be passed to timer callback function */
        .arg = NULL,
        .name = "one-shot"};

    
    ESP_ERROR_CHECK(esp_timer_create(&oneshot_timer_args, &oneshot_timer));
    // ESP_ERROR_CHECK(esp_timer_stop(oneshot_timer));
    // ESP_ERROR_CHECK(esp_timer_start_once(oneshot_timer, time));
}

void frequency_init(void)
{
    pcnt_init();
    timer_init(PULSE_SAMPLE_TIME); //1 seconde
}

void frequency_deinit(void)
{
    timer_mes = false;
    esp_timer_delete(oneshot_timer);
    //pcnt_isr_handler_remove(unit);
}

uint32_t frequency_hz(void)
{
    uint32_t frequency=0;
    uint32_t count=0;
    timer_mes = true;
    pulse_count = 0;
    // pcnt_unit_enable(pcnt_unit);
    pcnt_counter_clear(unit);
    esp_timer_start_once(oneshot_timer, PULSE_SAMPLE_TIME);
    pcnt_counter_resume(unit);
    while (timer_mes)
    {
        vTaskDelay(10);
        // count++;
        // if (count > (PULSE_SAMPLE_TIME / 10000*2))
        // {
        //     // pcnt_unit_stop(pcnt_unit);
        //     // pcnt_unit_disable(pcnt_unit);
        //     // pcnt_unit_get_count(pcnt_unit, &pulse_count);
        //     printf("error\n");
        //     pulse_count = 0;
        //     break;
        // } 
    }
    frequency = pulse_count *((float)(1000000 / PULSE_SAMPLE_TIME )* 0.5) ;
    pulse_count = 0;
    count = 0;
    printf("caculate frequency %ld\r\n", frequency);
    // pcnt_unit_stop(pcnt_unit);

    return frequency;
}