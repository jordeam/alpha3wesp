#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "pins.h"

void ledc_pwm_config(void) {
  /*
   * Prepare and set configuration of timers
   * that will be used by LED Controller
   */
  ledc_timer_config_t ledc_ls_timer = {
    .duty_resolution = LEDC_TIMER_16_BIT, // resolution of PWM duty
    .freq_hz = 60,                      // frequency of PWM signal
    .speed_mode = LEDC_LOW_SPEED_MODE,           // timer mode
    .timer_num = LEDC_TIMER_1,            // timer index
    .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
  };
  // Set configuration of timer0 for high speed channels
  ledc_timer_config(&ledc_ls_timer);

  ledc_timer_config_t ledc_hs_timer = {
    .duty_resolution = LEDC_TIMER_10_BIT,  // resolution of PWM duty
    .freq_hz = 40000,                      // frequency of PWM signal
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .timer_num = LEDC_TIMER_0,
    .clk_cfg = LEDC_AUTO_CLK              // Auto select the source clock
  };
  // Prepare and set configuration of timer1 for low speed channels
  ledc_timer_config(&ledc_hs_timer);

  ledc_channel_config_t ledc_channel_0 = {
    .channel    = LEDC_CHANNEL_0,
    .duty       = 1 << 15,
    .gpio_num   = OSC60,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = LEDC_TIMER_1
  };

  /* ledc_channel_config_t ledc_channel_7 = { */
  /*   .channel    = LEDC_CHANNEL_7, */
  /*   .duty       = 1 << 15, */
  /*   .gpio_num   = OSC40K, */
  /*   .speed_mode = LEDC_LOW_SPEED_MODE, */
  /*   .hpoint     = 0, */
  /*   .timer_sel  = LEDC_TIMER_1 */
  /* }; */

  ledc_channel_config_t ledc_channel_1 = {
    .channel    = LEDC_CHANNEL_1,
    .duty       = 0,
    .gpio_num   = GATE1,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = LEDC_TIMER_0
  };

  ledc_channel_config_t ledc_channel_2 = {
    .channel    = LEDC_CHANNEL_2,
    .duty       = 0,
    .gpio_num   = GATE2,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = LEDC_TIMER_0
  };

  ledc_channel_config_t ledc_channel_3 = {
    .channel    = LEDC_CHANNEL_3,
    .duty       = 0,
    .gpio_num   = GATE3,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = LEDC_TIMER_0
  };

  ledc_channel_config_t ledc_channel_4 = {
    .channel    = LEDC_CHANNEL_4,
    .duty       = 0,
    .gpio_num   = GATE4,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = LEDC_TIMER_0
  };

  ledc_channel_config_t ledc_channel_5 = {
    .channel    = LEDC_CHANNEL_5,
    .duty       = 0,
    .gpio_num   = GATE5,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = LEDC_TIMER_0
  };

  ledc_channel_config_t ledc_channel_6 = {
    .channel    = LEDC_CHANNEL_6,
    .duty       = 0,
    .gpio_num   = GATE6,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = LEDC_TIMER_0
  };

  ledc_channel_config(&ledc_channel_0);
  ledc_channel_config(&ledc_channel_1);
  ledc_channel_config(&ledc_channel_2);
  ledc_channel_config(&ledc_channel_3);
  ledc_channel_config(&ledc_channel_4);
  ledc_channel_config(&ledc_channel_5);
  ledc_channel_config(&ledc_channel_6);
}
