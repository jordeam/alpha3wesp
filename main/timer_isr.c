#include <stddef.h>
#include "esp_intr_alloc.h"
#include "esp_attr.h"
#include "driver/timer.h"

static intr_handle_t s_timer_handle;

static void timer_isr(void* arg)
{
  TIMERG0.int_clr_timers.t0 = 1;
  TIMERG0.hw_timer[0].config.alarm_en = 1;

  // your code, runs in the interrupt
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
  init_timer(50);
}
