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

/* Outputs:
   GPIO2: internal LED
   GPIO16: Oscilator 40kHz,
   GPIO17, 18, 19: positive semicycle phases 1, 2 and 3,
   GPIO25, 26, 27: negative senicycle phases 1, 2 and 3 */
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<2) | (1ULL<<16) | (1ULL<<17) | (1ULL<<18) | (1ULL<<19) | (1ULL<<25) | (1ULL<<26) | (1ULL<<27))

/* Inputs:
   GPIO4: sync
   GPIO34: ADC input angle
 */
#define GPIO_INPUT_PIN_SEL  ((1ULL<<4) | (1ULL<<34))

int sync;
uint32_t cnt, cnt_max = 0;
static intr_handle_t s_timer_handle;

static void timer_isr(void* arg)
{
  static int sync_old = 1;
  TIMERG0.int_clr_timers.t0 = 1;
  TIMERG0.hw_timer[0].config.alarm_en = 1;

  /* read SYNC */
  sync = gpio_get_level(4);

  if (sync && !sync_old) {
    cnt_max = cnt;
    cnt = 0;
  }
  else
    cnt++;
  sync_old = sync;

  /* eval outputs */
  /* refresh output pins */
}

void init_timer(int timer_period_us)
{
  timer_config_t config = {
    .alarm_en = true,
    .counter_en = false,
    .intr_type = TIMER_INTR_LEVEL,
    .counter_dir = TIMER_COUNT_UP,
    .auto_reload = true,
    .divider = 80   /* 1 us per tick */
  };

  timer_init(TIMER_GROUP_0, TIMER_0, &config);
  timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
  timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, timer_period_us);
  timer_enable_intr(TIMER_GROUP_0, TIMER_0);
  timer_isr_register(TIMER_GROUP_0, TIMER_0, &timer_isr, NULL, 0, &s_timer_handle);

  timer_start(TIMER_GROUP_0, TIMER_0);
}

void app_main()
{
  /* init GPIOs */
  gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
    .pull_down_en = 0,
    .pull_up_en = 0
  };
  //configure GPIO with the given settings
  gpio_config(&io_conf);

  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
  io_conf.mode = GPIO_MODE_INPUT;
  io_conf.pull_up_en = 0;
  io_conf.pull_down_en = 0;
  gpio_config(&io_conf);


  init_timer(50);

  int cnt = 0;
  for (;;cnt = !cnt) {
    vTaskDelay(200 / portTICK_RATE_MS);
    gpio_set_level(2, cnt % 2);
  }
}
