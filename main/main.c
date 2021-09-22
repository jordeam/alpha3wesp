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

#define GPIO_OUTPUT_PIN_SEL  (port_bit(LED_GPIO) | \
                              port_bit(GATE1) | port_bit(GATE3) | \
                              port_bit(GATE5) | port_bit(GATE4) | \
                              port_bit(GATE6) | port_bit(GATE2) | \
                              port_bit(SIGINT) | port_bit(SIGAD))

#define GPIO_INPUT_PIN_SEL  (port_bit(SYNC_GPIO) | port_bit(ADC_GPIO))

int sync;
int cnt, cnt_max = -1;
/* Maximum counter value used in last eval */
int cnt_max_e = 0;

/* the transitions */
int gate_1_rise, gate_1_fall, gate_2_rise, gate_2_fall,
  gate_3_rise, gate_3_fall, gate_4_rise, gate_4_fall,
  gate_5_rise, gate_5_fall, gate_6_rise, gate_6_fall;

static intr_handle_t s_timer_handle;
/* the alpha trigger angle in degrees */
float alpha = 180;

static void timer_isr(void* arg) {
  static int sync_old = 1;

  gpio_set_level(SIGINT, 1);

  TIMERG0.int_clr_timers.t0 = 1;
  TIMERG0.hw_timer[0].config.alarm_en = 1;

  /* read SYNC */
  sync = gpio_get_level(SYNC_GPIO);

  if (sync && !sync_old && /* jitter ? */cnt > 20) {
    if (cnt_max < 0)
      cnt_max++;
    else if (cnt_max == 0)
      cnt_max = cnt;
    else {
      cnt_max += cnt;
      cnt_max >>= 1;
      /* Verify if Gates 4, 5 and 6 are higher than cnt */
      if (gate_4_fall >= cnt)
        gpio_set_level(GATE4, 0);
      if (gate_5_fall >= cnt)
        gpio_set_level(GATE5, 0);
      if (gate_6_fall >= cnt)
        gpio_set_level(GATE6, 0);
      if (gate_5_rise >= cnt)
        gpio_set_level(GATE5, 1);
      if (gate_4_fall >= cnt)
        gpio_set_level(GATE4, 0);
      if (gate_6_rise >= cnt)
        gpio_set_level(GATE6, 1);
    }
    cnt = 0;
  }

  /* do nothing if counter maximum is equal or less than zero*/
  if (cnt_max > 0) {
    /* refresh output pins */
    if (cnt == gate_1_rise)
      gpio_set_level(GATE1, 1);
    else if (cnt == gate_1_fall)
      gpio_set_level(GATE1, 0);
    if (cnt == gate_2_rise)
      gpio_set_level(GATE2, 1);
    else if (cnt == gate_2_fall)
      gpio_set_level(GATE2, 0);
    if (cnt == gate_3_rise)
      gpio_set_level(GATE3, 1);
    else if (cnt == gate_3_fall)
      gpio_set_level(GATE3, 0);
    if (cnt == gate_4_rise)
      gpio_set_level(GATE4, 1);
    else if (cnt == gate_4_fall)
      gpio_set_level(GATE4, 0);
    if (cnt == gate_5_rise)
      gpio_set_level(GATE5, 1);
    else if (cnt == gate_5_fall)
      gpio_set_level(GATE5, 0);
    if (cnt == gate_6_rise)
      gpio_set_level(GATE6, 1);
    else if (cnt == gate_6_fall)
      gpio_set_level(GATE6, 0);
  }

  /* increment counter */
  cnt++;
  /* refresh sync_old */
  sync_old = sync;
  /* flag interrupt exiting */
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

/* task to eval all trigger event times */
void eval_triggers(void * pvParams) {
  for (;;) {
    gpio_set_level(SIGAD, 1);
    int val = adc1_get_raw(ADC1_CHANNEL_0);
    gpio_set_level(SIGAD, 0);

    cnt_max_e = cnt_max;
    /* verify if it detected the first sync pulse */
    if (cnt_max_e != 0) {
      if (alpha > 180.0f)
        alpha = 180.0f;
      float alpha_n = alpha / 360.0;
      gate_1_rise = cnt_max_e * alpha_n;
      gate_1_fall = cnt_max_e * 0.5;
      gate_2_rise = cnt_max_e * (alpha_n + 0.1666);
      gate_2_fall = cnt_max_e * 0.6666;
      gate_3_rise = cnt_max_e * (alpha_n + 0.3333);
      gate_3_fall = cnt_max_e * 0.8333;
      gate_4_rise = cnt_max_e * (alpha_n + 0.5);
      gate_4_fall = cnt_max_e - 1;
      gate_5_rise = cnt_max_e * (alpha_n + 0.6666);
      if (gate_5_rise >= cnt_max_e)
        gate_5_rise -= cnt_max_e;
      gate_5_fall = cnt_max_e * 0.1666;
      gate_6_rise = cnt_max_e * (alpha_n + 0.8333);
      if (gate_6_rise >= cnt_max_e)
        gate_6_rise -= cnt_max_e;
      gate_6_fall = cnt_max_e * 0.3333;
    }

    /* wait for something ? */
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void led_task(void * pvParams) {
  for (int cnt = 0;;cnt = !cnt) {
    vTaskDelay(pdMS_TO_TICKS(200));
    gpio_set_level(LED_GPIO, cnt % 2);
  }
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

  /* configure ADC raw */
  adc_config();

  /* register 50us interrupt SR */
  init_timer(50);

  /* TODO: clear this */
  /* alpha for test purposes */
  alpha = 120;

  xTaskCreate(led_task, "led_task", 4096, NULL, 5, NULL);
  xTaskCreate(eval_triggers, "eval_triggers", 4096, NULL, 4, NULL);
}
