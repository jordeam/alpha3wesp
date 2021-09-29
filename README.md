# alpha3wesp
Triphase trigger angle control using ESP32

## Pin connection

| ESP32 GPIO | Function |
|------------|----------|
| 15 | 60Hz square oscilator output for debug |
| 16 | 40kHz output oscilator for TPs |
| 17 | Gate of SCR 1 (Q1) |
| 18 | Gate of SCR 3 (Q3) |
| 19 | Gate of SCR 5 (Q5) |
| 25 | Gate of SCR 4 (Q4) |
| 26 | Gate of SCR 6 (Q6) |
| 27 | Gate of SCR 2 (Q2) |
| 4  | Grid Synchronism input |
| 34 | Analog input for alpha trigger angle |

The device works in 50Hz or 60Hz automatically.

SCR power bridge has its positive cycle devices tagged as Q1, for phase a, Q3 for phase b, and Q5 for phase c. The negative cycle for phase a is SCR number 4 (Q4), for phase b is Q6 and for phase c is Q2. This produces a trigger sequence in order, from Q1 to Q6.

## Circuit Example

An example of usage can be seen in [circuit-1](doc/example-circuit-1.pdf). In that circuit, a triphase full-bridge (or two way) rectifier is shown. Note the numbering of thyristors Q1 to Q6, it is very important to match with the ESP32 outputs. Also, certify that phases A, B and C are in the right sequence. For simplification, only one Gate Driver block is show, but it needs to be one for each thyristor.

An input of voltage from 0 to 2.5V means o to 180 degrees of trigger for each SCR.

## TODO

- accept inputs from UART, SPI, I2C, CAN and pulse width.
- implement reversion capability for AC three-phase controllers.
- as always, improve docs...

## Thanks

To all free software developers, thank you!
