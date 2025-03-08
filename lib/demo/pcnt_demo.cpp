#if 0
#include <Arduino.h>

#include "rk816.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/ledc.h"
#include "driver/pcnt.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
static const char *TAG = "example";

#define PCNT_H_LIM_VAL      10
#define PCNT_L_LIM_VAL     -10
#define PCNT_THRESH1_VAL    5
#define PCNT_THRESH0_VAL   -5
#define PCNT_INPUT_SIG_IO   6  // Pulse Input GPIO
#define PCNT_INPUT_CTRL_IO  5  // Control GPIO HIGH=count up, LOW=count down
#define LEDC_OUTPUT_IO      7 // Output GPIO of a sample 1 Hz pulse generator
 
 typedef struct {
    int unit;  // the PCNT unit that originated an interrupt
    uint32_t status; // information on the event type that caused the interrupt
} pcnt_evt_t;

pcnt_unit_t pcnt_unit = PCNT_UNIT_0;
int16_t count = 0,status;
pcnt_evt_t evt;
xQueueHandle pcnt_evt_queue;

static void ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer;
    ledc_timer.speed_mode       = LEDC_LOW_SPEED_MODE;
    ledc_timer.timer_num        = LEDC_TIMER_1;
    ledc_timer.duty_resolution  = LEDC_TIMER_10_BIT;
    ledc_timer.freq_hz          = 1;  // set output frequency at 1 Hz
    ledc_timer.clk_cfg = LEDC_AUTO_CLK;
    ledc_timer_config(&ledc_timer);

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel;
    ledc_channel.speed_mode = LEDC_LOW_SPEED_MODE;
    ledc_channel.channel    = LEDC_CHANNEL_1;
    ledc_channel.timer_sel  = LEDC_TIMER_1;
    ledc_channel.intr_type  = LEDC_INTR_DISABLE;
    ledc_channel.gpio_num   = LEDC_OUTPUT_IO;
    ledc_channel.duty       = 100; // set duty at about 10%
    ledc_channel.hpoint     = 0;
    ledc_channel_config(&ledc_channel);
}

 
static void pcnt_example_init(pcnt_unit_t unit)
{
    /* Prepare configuration for the PCNT unit */
    pcnt_config_t pcnt_config; 
        // Set PCNT input signal and control GPIOs
        pcnt_config.pulse_gpio_num = PCNT_INPUT_SIG_IO,
        pcnt_config.ctrl_gpio_num = PCNT_INPUT_CTRL_IO,
        pcnt_config.channel = PCNT_CHANNEL_0,
        pcnt_config.unit = unit,
        // What to do on the positive / negative edge of pulse input?
        pcnt_config.pos_mode = PCNT_COUNT_INC,   // Count up on the positive edge
        pcnt_config.neg_mode = PCNT_COUNT_DIS,   // Keep the counter value on the negative edge
        // What to do when control input is low or high?
        pcnt_config.lctrl_mode = PCNT_MODE_REVERSE, // Reverse counting direction if low
        pcnt_config.hctrl_mode = PCNT_MODE_KEEP,    // Keep the primary counter mode if high
        // Set the maximum and minimum limit values to watch
        pcnt_config.counter_h_lim = PCNT_H_LIM_VAL,
        pcnt_config.counter_l_lim = PCNT_L_LIM_VAL,
    //};
    /* Initialize PCNT unit */
    pcnt_unit_config(&pcnt_config);

    /* Configure and enable the input filter */
    pcnt_set_filter_value(unit, 100);
    pcnt_filter_enable(unit);

    /* Set threshold 0 and 1 values and enable events to watch */
 
    /* Enable events on zero, maximum and minimum limit values */
    pcnt_event_enable(unit, PCNT_EVT_ZERO);
    pcnt_event_enable(unit, PCNT_EVT_H_LIM);
    pcnt_event_enable(unit, PCNT_EVT_L_LIM);

    /* Initialize PCNT's counter */
    pcnt_counter_pause(unit);
    pcnt_counter_clear(unit);

    /* Install interrupt service and add isr callback handler */
 
    /* Everything is set up, now go to counting */
    pcnt_counter_resume(unit);
}


void setup()
{
    Serial.begin( 115200 ); 
 
    delay(5000);
    rk816_init_power();
    delay(2000);
    //rk816_init_power();
    ledc_init();
printf("123\r\n");
    /* Initialize PCNT event queue and PCNT functions */
     
    printf("123\r\n");
    pcnt_example_init(pcnt_unit);
 printf("123\r\n");
}
portBASE_TYPE res;
void loop()
{

    pcnt_get_counter_value(pcnt_unit, &count);
    printf("cnt: %d\r\n", count);
    delay(500);
}
#endif