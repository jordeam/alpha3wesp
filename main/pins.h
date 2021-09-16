#ifndef _pins_h
#define _pins_h

/*
  Outputs:
  GPIO2: internal LED
  GPIO16: Oscilator 40kHz,
  G1P, G2P and G3P: positive semicycle phases 1, 2 and 3,
  G1N, G2N and G3N: negative senicycle phases 1, 2 and 3
*/

#define LED_GPIO 2
#define OSC60 15
#define OSC40K 16
#define G1P 17
#define G2P 18
#define G3P 19
#define G1N 25
#define G2N 26
#define G3N 27

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
