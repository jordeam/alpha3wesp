#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "pins.h"

#if CONFIG_IDF_TARGET_ESP32
#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO       (OSC40K)
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0
#endif
#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE
#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32C3
#define LEDC_LS_CH0_GPIO       (OSC40K)
#define LEDC_LS_CH0_CHANNEL    LEDC_CHANNEL_0
#endif
#define LEDC_LS_CH1_GPIO       (OSC60)
#define LEDC_LS_CH1_CHANNEL    LEDC_CHANNEL_1

#define LEDC_TEST_CH_NUM       2
#define LEDC_TEST_DUTY         4000
#define LEDC_TEST_FADE_TIME    3000

void ledc_pwm_config(void) {
    /*
     * Prepare and set configuration of timers
     * that will be used by LED Controller
     */
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_16_BIT, // resolution of PWM duty
        .freq_hz = 60,                      // frequency of PWM signal
        .speed_mode = LEDC_LS_MODE,           // timer mode
        .timer_num = LEDC_LS_TIMER,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };
    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer);
#ifdef CONFIG_IDF_TARGET_ESP32
    // Prepare and set configuration of timer1 for low speed channels
    ledc_timer.duty_resolution = LEDC_TIMER_10_BIT; // resolution of PWM duty
    ledc_timer.freq_hz = 40000;                      // frequency of PWM signal
    ledc_timer.speed_mode = LEDC_HS_MODE;
    ledc_timer.timer_num = LEDC_HS_TIMER;
    ledc_timer_config(&ledc_timer);
#endif
    /*
     * Prepare individual configuration
     * for each channel of LED Controller
     * by selecting:
     * - controller's channel number
     * - output duty cycle, set initially to 0
     * - GPIO number where LED is connected to
     * - speed mode, either high or low
     * - timer servicing selected channel
     *   Note: if different channels use one timer,
     *         then frequency and bit_num of these channels
     *         will be the same
     */
#if CONFIG_IDF_TARGET_ESP32
    ledc_channel_config_t ledc_channel_0 = {
      .channel    = LEDC_HS_CH0_CHANNEL,
      .duty       = (int)((1 << 10) * 0.4),
      .gpio_num   = LEDC_HS_CH0_GPIO,
      .speed_mode = LEDC_HS_MODE,
      .hpoint     = 0,
      .timer_sel  = LEDC_HS_TIMER
    };
#elif CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32C3
    ledc_channel_config_t ledc_channel_0 = {
      .channel    = LEDC_LS_CH0_CHANNEL,
      .duty       = (int)((1 << 10) * 0.4),
      .gpio_num   = LEDC_LS_CH0_GPIO,
      .speed_mode = LEDC_LS_MODE,
      .hpoint     = 0,
      .timer_sel  = LEDC_LS_TIMER
    };
#endif
    ledc_channel_config_t ledc_channel_1 = {
      .channel    = LEDC_LS_CH1_CHANNEL,
      .duty       = 1 << 15,
      .gpio_num   = LEDC_LS_CH1_GPIO,
      .speed_mode = LEDC_LS_MODE,
      .hpoint     = 0,
      .timer_sel  = LEDC_LS_TIMER
    };

    ledc_channel_config(&ledc_channel_0);
    ledc_channel_config(&ledc_channel_1);
}
