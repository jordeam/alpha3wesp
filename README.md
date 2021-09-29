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

