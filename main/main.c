#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_intr_alloc.h"
#include "esp_attr.h"
#include "driver/timer.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "pins.h"
#include "ledc_pwm.h"
#include "adc_mod.h"

#define GPIO_OUTPUT_PIN_SEL  (port_bit(LED_GPIO) | \
                              port_bit(SIGINT) | port_bit(SIGAD))

#define GPIO_INPUT_PIN_SEL  (port_bit(SYNC_GPIO) | port_bit(ADC_GPIO))

#define GATE_DUTY ((int)((1 << 10) * 0.4))

int sync;
int cnt, cnt_max = -1;
/* Maximum counter value used in last eval */
int cnt_max_e = 0;

/* the transitions */
struct tr {
  int rise[6], fall[6];
};

typedef struct tr tr_t;

tr_t gate;

static intr_handle_t s_timer_handle;
/* the alpha trigger angle in degrees */
float alpha = 60;

static void timer_isr(void* arg) {
  static int sync_old = 1;
  static tr_t g;

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
      memcpy(&g, &gate, sizeof(tr_t));

      /* Verify if Gates 4, 5 and 6 are higher than cnt */
      if (g.fall[3] >= cnt) {
        /* gpio_set_level(GATE4, 0); */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, 0);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);
      }
      if (g.fall[4] >= cnt) {
        /* gpio_set_level(GATE5, 0); */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, 0);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);
      }
      if (g.fall[5] >= cnt) {
        /* gpio_set_level(GATE6, 0); */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, 0);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
      }
      if (g.rise[4] >= cnt) {
        /* gpio_set_level(GATE5, 1); */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, GATE_DUTY);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);
      }
      if (g.fall[3] >= cnt) {
        /* gpio_set_level(GATE4, 0); */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, 0);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);
      }
      if (g.rise[5] >= cnt) {
        /* gpio_set_level(GATE6, 1); */
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, GATE_DUTY);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
      }
    }
    cnt = 0;
  }

  /* do nothing if counter maximum is equal or less than zero*/
  if (cnt_max > 0) {
    /* refresh output pins */
    if (cnt == g.rise[0]) {
      /* gpio_set_level(GATE1, 1); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, GATE_DUTY);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    }
    else if (cnt == g.fall[0]) {
      /* gpio_set_level(GATE1, 0); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 0);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    }
    if (cnt == g.rise[1]) {
      /* gpio_set_level(GATE2, 1); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, GATE_DUTY);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);
    }
    else if (cnt == g.fall[1]) {
      /* gpio_set_level(GATE2, 0); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, 0);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);
    }
    if (cnt == g.rise[2]) {
      /* gpio_set_level(GATE3, 1); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, GATE_DUTY);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
    }
    else if (cnt == g.fall[2]) {
      /* gpio_set_level(GATE3, 0); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, 0);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);
    }
    if (cnt == g.rise[3]) {
      /* gpio_set_level(GATE4, 1); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, GATE_DUTY);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);
    }
    else if (cnt == g.fall[3]) {
      /* gpio_set_level(GATE4, 0); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, 0);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4);
    }
    if (cnt == g.rise[4]) {
      /* gpio_set_level(GATE5, 1); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, GATE_DUTY);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);
    }
    else if (cnt == g.fall[4]) {
      /* gpio_set_level(GATE5, 0); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5, 0);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_5);
    }
    if (cnt == g.rise[5]) {
      /* gpio_set_level(GATE6, 1); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, GATE_DUTY);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
    }
    else if (cnt == g.fall[5]) {
      /* gpio_set_level(GATE6, 0); */
      ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6, 0);
      ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_6);
    }
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

    alpha = 180.0f * val / (1 << 12);
    cnt_max_e = cnt_max;
    /* verify if it detected the first sync pulse */
    if (cnt_max_e != 0) {
      if (alpha > 180.0f)
        alpha = 180.0f;
      float alpha_n = alpha / 360.0;
      gate.rise[0] = cnt_max_e * alpha_n;
      gate.fall[0] = cnt_max_e * 0.5;
      gate.rise[1] = cnt_max_e * (alpha_n + 0.1666);
      gate.fall[1] = cnt_max_e * 0.6666;
      gate.rise[2] = cnt_max_e * (alpha_n + 0.3333);
      gate.fall[2] = cnt_max_e * 0.8333;
      gate.rise[3] = cnt_max_e * (alpha_n + 0.5);
      gate.fall[3] = cnt_max_e - 1;
      gate.rise[4] = cnt_max_e * (alpha_n + 0.6666);
      if (gate.rise[4] >= cnt_max_e)
        gate.rise[4] -= cnt_max_e;
      gate.fall[4] = cnt_max_e * 0.1666;
      gate.rise[5] = cnt_max_e * (alpha_n + 0.8333);
      if (gate.rise[5] >= cnt_max_e)
        gate.rise[5] -= cnt_max_e;
      gate.fall[5] = cnt_max_e * 0.3333;
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

  xTaskCreate(led_task, "led_task", 4096, NULL, 5, NULL);
  xTaskCreate(eval_triggers, "eval_triggers", 4096, NULL, 4, NULL);
}
