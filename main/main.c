#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_intr_alloc.h"
#include "esp_attr.h"
#include "driver/timer.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "pins.h"
#include "ledc_pwm.h"
#include "adc_mod.h"

#define GPIO_OUTPUT_PIN_SEL  (port_bit(LED_GPIO) | port_bit(G1P) | port_bit(G2P) | port_bit(G3P) | port_bit(G1N) | port_bit(G2N) | port_bit(G3N) | port_bit(SIGINT) | port_bit(SIGAD))

#define GPIO_INPUT_PIN_SEL  (port_bit(SYNC_GPIO) | port_bit(ADC_GPIO))

int sync;
uint32_t cnt, cnt_max = 0;
static intr_handle_t s_timer_handle;

static void timer_isr(void* arg) {
  static int sync_old = 1;
  gpio_set_level(SIGINT, 1);

  TIMERG0.int_clr_timers.t0 = 1;
  TIMERG0.hw_timer[0].config.alarm_en = 1;

  /* read SYNC */
  sync = gpio_get_level(SYNC_GPIO);

  if (sync && !sync_old) {
    cnt_max = cnt;
    cnt = 0;
  }
  else
    cnt++;
  sync_old = sync;

  /* eval outputs */
  /* refresh output pins */

  gpio_set_level(SIGAD, 1);
  adc1_get_raw(ADC_CHANNEL_6);
  gpio_set_level(SIGAD, 0);

  gpio_set_level(SIGINT, 0);
}

void init_timer(int timer_period_us)
{
  timer_config_t timer_config = {
    .alarm_en = true,
    .counter_en = false,
    .intr_type = TIMER_INTR_LEVEL,
    .counter_dir = TIMER_COUNT_UP,
    .auto_reload = true,
    .divider = 80   /* 1 us per tick */
  };

  timer_init(TIMER_GROUP_0, TIMER_0, &timer_config);
  timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
  timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, timer_period_us);
  timer_enable_intr(TIMER_GROUP_0, TIMER_0);
  timer_isr_register(TIMER_GROUP_0, TIMER_0, &timer_isr, NULL, 0, &s_timer_handle);

  timer_start(TIMER_GROUP_0, TIMER_0);
}

void app_main()
{
  /* init GPIOs */
  gpio_config_t io_conf_o = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
    .pull_down_en = 0,
    .pull_up_en = 0
  };
  //configure GPIO with the given settings
  gpio_config(&io_conf_o);

  gpio_config_t io_conf_i = {
    .intr_type = GPIO_INTR_DISABLE,
    .pin_bit_mask = GPIO_INPUT_PIN_SEL,
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = 0,
    .pull_down_en = 0,
  };
  gpio_config(&io_conf_i);

  /* configure LED PWMs */
  ledc_pwm_config();

  adc_config();

  /* register 50us interrupt SR */
  init_timer(500);

  for (int cnt = 0;;cnt = !cnt) {
    vTaskDelay(pdMS_TO_TICKS(200));
    gpio_set_level(LED_GPIO, cnt % 2);
  }
}
