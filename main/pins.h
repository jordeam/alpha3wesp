#ifndef _pins_h
#define _pins_h

/*
  Outputs:
  GPIO2: internal LED
  GPIO16: Oscilator 40kHz,
  Gate1, Gate3 and Gate5: positive semicycle phases 1, 2 and 3,
  Gate4, Gate6 and Gate2: negative senicycle phases 1, 2 and 3
*/

#define LED_GPIO 2
#define OSC60 15
#define OSC40K 16
#define GATE1 17
#define GATE3 18
#define GATE5 19
#define GATE4 25
#define GATE6 26
#define GATE2 27

#define SIGINT 14
#define SIGAD 33

/* Inputs:
   SYNC_GPIO: sync
   ADC_GPIO: ADC input angle
*/
#define SYNC_GPIO 4
#define ADC_GPIO 34

#define port_bit(x) (1ULL<<x)

#endif
