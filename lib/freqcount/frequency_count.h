
#pragma once
#ifndef FREQUENCY_COUNT_H
#define FREQUENCY_COUNT_H

#include <stdint.h>
#include "driver/pcnt.h"
#include "driver/rmt.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
    gpio_num_t pcnt_gpio;                   ///< count events on this GPIO
    pcnt_unit_t pcnt_unit;                  ///< PCNT unit to use for counting
    pcnt_channel_t pcnt_channel;            ///< PCNT channel to use for counting
    gpio_num_t rmt_gpio;                    ///< used by RMT to define a sampling window
    rmt_channel_t rmt_channel;              ///< The RMT channel to use
    uint8_t rmt_clk_div;                    ///< RMT pulse length, as a divider of the APB clock
    uint8_t rmt_max_blocks;                 ///< Maximum number of RMT RAM blocks that can be used by task. Each block provides 64 RMT items and each item can provide a window duration of up to 2 * 32767 = 65534 periods.
    float sampling_period_seconds;          ///< time (in seconds) between start of adjacent samples
    float sampling_window_seconds;          ///< sample window length (in seconds)
    uint16_t filter_length;                 ///< counter filter length in APB cycles
    void (*window_start_callback)(void);    ///< called just prior to starting a sampling window
    void (*frequency_update_callback)(double hz);  ///< called each time a frequency is determined
} frequency_count_configuration_t;

    void frequency_init(void);
    void frequency_deinit(void);
    uint32_t frequency_hz(void);

#ifdef __cplusplus
}
#endif

#endif // FREQUENCY_COUNT
