EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Comparator:LM311 U1
U 1 1 615464FE
P 4700 2250
F 0 "U1" H 5044 2296 50  0000 L CNN
F 1 "LM311" H 5044 2205 50  0000 L CNN
F 2 "" H 4700 2250 50  0001 C CNN
F 3 "https://www.st.com/resource/en/datasheet/lm311.pdf" H 4700 2250 50  0001 C CNN
	1    4700 2250
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D2
U 1 1 6154730E
P 4100 2400
F 0 "D2" V 4054 2480 50  0000 L CNN
F 1 "1N4148" V 4145 2480 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4100 2225 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4100 2400 50  0001 C CNN
	1    4100 2400
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D1
U 1 1 615494E0
P 3700 2400
F 0 "D1" V 3746 2320 50  0000 R CNN
F 1 "1N4148" V 3655 2320 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3700 2225 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3700 2400 50  0001 C CNN
	1    3700 2400
	0    -1   -1   0   
$EndComp
$Comp
L Device:Transformer_1P_1S T1
U 1 1 6154B597
P 2950 2350
F 0 "T1" H 2950 2731 50  0000 C CNN
F 1 "Transformer_1P_1S" H 2950 2640 50  0000 C CNN
F 2 "" H 2950 2350 50  0001 C CNN
F 3 "~" H 2950 2350 50  0001 C CNN
	1    2950 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6154D190
P 3500 2150
F 0 "R1" V 3293 2150 50  0000 C CNN
F 1 "2K2" V 3384 2150 50  0000 C CNN
F 2 "" V 3430 2150 50  0001 C CNN
F 3 "~" H 3500 2150 50  0001 C CNN
	1    3500 2150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6154E48E
P 4700 2650
F 0 "#PWR03" H 4700 2400 50  0001 C CNN
F 1 "GND" H 4705 2477 50  0000 C CNN
F 2 "" H 4700 2650 50  0001 C CNN
F 3 "" H 4700 2650 50  0001 C CNN
	1    4700 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 61550F12
P 5000 2050
F 0 "R2" H 5070 2096 50  0000 L CNN
F 1 "4K7" H 5070 2005 50  0000 L CNN
F 2 "" V 4930 2050 50  0001 C CNN
F 3 "~" H 5000 2050 50  0001 C CNN
	1    5000 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2150 3700 2150
Wire Wire Line
	4100 2250 4100 2150
Connection ~ 4100 2150
Wire Wire Line
	4100 2150 4400 2150
Wire Wire Line
	3700 2250 3700 2150
Connection ~ 3700 2150
Wire Wire Line
	3700 2150 4100 2150
Wire Wire Line
	3700 2550 4100 2550
Connection ~ 4100 2550
Wire Wire Line
	4100 2550 4400 2550
Connection ~ 4600 2550
Wire Wire Line
	4600 2550 4700 2550
Wire Wire Line
	4700 2650 4700 2550
Connection ~ 4700 2550
$Comp
L power:+12V #PWR02
U 1 1 61561A7D
P 4600 1700
F 0 "#PWR02" H 4600 1550 50  0001 C CNN
F 1 "+12V" H 4615 1873 50  0000 C CNN
F 2 "" H 4600 1700 50  0001 C CNN
F 3 "" H 4600 1700 50  0001 C CNN
	1    4600 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 61565B49
P 4300 1850
F 0 "C1" H 4415 1896 50  0000 L CNN
F 1 "100nF" H 4415 1805 50  0000 L CNN
F 2 "" H 4338 1700 50  0001 C CNN
F 3 "~" H 4300 1850 50  0001 C CNN
	1    4300 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 6156684B
P 4300 2000
F 0 "#PWR01" H 4300 1750 50  0001 C CNN
F 1 "GND" H 4305 1827 50  0000 C CNN
F 2 "" H 4300 2000 50  0001 C CNN
F 3 "" H 4300 2000 50  0001 C CNN
	1    4300 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1700 4600 1700
Wire Wire Line
	4600 1700 4600 1950
Connection ~ 4600 1700
Wire Wire Line
	5000 2250 5000 2200
Wire Wire Line
	5000 1900 5000 1850
$Comp
L power:+3.3V #PWR04
U 1 1 6156C66C
P 5000 1850
F 0 "#PWR04" H 5000 1700 50  0001 C CNN
F 1 "+3.3V" H 5015 2023 50  0000 C CNN
F 2 "" H 5000 1850 50  0001 C CNN
F 3 "" H 5000 1850 50  0001 C CNN
	1    5000 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2350 4400 2550
Connection ~ 4400 2550
Wire Wire Line
	4400 2550 4600 2550
$Comp
L SEL0401:ESP32-30PIN U2
U 1 1 61582E4B
P 6150 1350
F 0 "U2" H 6450 1475 50  0000 C CNN
F 1 "ESP32-30PIN" H 6450 1384 50  0000 C CNN
F 2 "" H 6150 1350 50  0001 C CNN
F 3 "" H 6150 1350 50  0001 C CNN
	1    6150 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 2450 7200 2450
Wire Wire Line
	7200 2450 7200 3200
Wire Wire Line
	7200 3200 5450 3200
Wire Wire Line
	5450 3200 5450 2250
Wire Wire Line
	5450 2250 5000 2250
Connection ~ 5000 2250
Wire Wire Line
	6850 2250 7500 2250
Text Label 7400 2250 0    50   ~ 0
G1
Wire Wire Line
	6850 2050 7500 2050
Text Label 7400 2050 0    50   ~ 0
G3
Text Label 7400 1850 0    50   ~ 0
G5
$Comp
L 74xx:74HCT541 U3
U 1 1 6158AD08
P 8000 2050
F 0 "U3" H 8000 3031 50  0000 C CNN
F 1 "74HCT541" H 8000 2940 50  0000 C CNN
F 2 "" H 8000 2050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HCT541" H 8000 2050 50  0001 C CNN
	1    8000 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2150 5800 2150
Text Label 7400 2150 0    50   ~ 0
G4
Wire Wire Line
	6050 2250 5850 2250
Wire Wire Line
	7300 2150 7500 2150
Text Label 7400 1950 0    50   ~ 0
G6
Wire Wire Line
	6050 2350 5900 2350
Text Label 7400 1750 0    50   ~ 0
G2
Wire Wire Line
	5900 3100 7150 3100
Wire Wire Line
	7150 3100 7150 1750
Wire Wire Line
	7150 1750 7500 1750
Wire Wire Line
	5900 2350 5900 3100
Wire Wire Line
	5850 3150 7250 3150
Wire Wire Line
	5850 2250 5850 3150
Wire Wire Line
	7250 1950 7500 1950
Wire Wire Line
	7250 1950 7250 3150
Wire Wire Line
	5800 3250 7300 3250
Wire Wire Line
	5800 2150 5800 3250
Wire Wire Line
	7300 2150 7300 3250
Wire Wire Line
	6850 1950 7100 1950
Wire Wire Line
	7100 1950 7100 1850
Wire Wire Line
	7100 1850 7500 1850
Wire Wire Line
	7500 1650 7500 1550
Wire Wire Line
	7500 1250 8000 1250
$Comp
L power:+5V #PWR07
U 1 1 615A3E70
P 7500 1250
F 0 "#PWR07" H 7500 1100 50  0001 C CNN
F 1 "+5V" H 7515 1423 50  0000 C CNN
F 2 "" H 7500 1250 50  0001 C CNN
F 3 "" H 7500 1250 50  0001 C CNN
	1    7500 1250
	1    0    0    -1  
$EndComp
Connection ~ 7500 1250
$Comp
L Device:C C2
U 1 1 615A489E
P 7250 1400
F 0 "C2" H 7365 1446 50  0000 L CNN
F 1 "100nF" H 7365 1355 50  0000 L CNN
F 2 "" H 7288 1250 50  0001 C CNN
F 3 "~" H 7250 1400 50  0001 C CNN
	1    7250 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 615A536C
P 7250 1550
F 0 "#PWR06" H 7250 1300 50  0001 C CNN
F 1 "GND" H 7255 1377 50  0000 C CNN
F 2 "" H 7250 1550 50  0001 C CNN
F 3 "" H 7250 1550 50  0001 C CNN
	1    7250 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 615A5FA9
P 7000 2950
F 0 "#PWR05" H 7000 2700 50  0001 C CNN
F 1 "GND" H 7005 2777 50  0000 C CNN
F 2 "" H 7000 2950 50  0001 C CNN
F 3 "" H 7000 2950 50  0001 C CNN
	1    7000 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 2750 7000 2750
Wire Wire Line
	7000 2750 7000 2950
Wire Wire Line
	6050 2750 5950 2750
Wire Wire Line
	5950 2750 5950 2950
Wire Wire Line
	5950 2950 7000 2950
Connection ~ 7000 2950
Wire Wire Line
	6050 2850 6000 2850
Wire Wire Line
	6000 2850 6000 1250
Wire Wire Line
	6000 1250 7250 1250
Connection ~ 7250 1250
Wire Wire Line
	7250 1250 7500 1250
Wire Wire Line
	7500 1550 7500 1250
Connection ~ 7500 1550
Text GLabel 3400 5100 0    50   Input ~ 0
FASE_A
Text GLabel 3400 5250 0    50   Input ~ 0
FASE_B
Wire Wire Line
	2400 2150 2550 2150
Wire Wire Line
	2400 2550 2550 2550
Wire Wire Line
	7500 2450 7500 2550
Wire Wire Line
	7500 2850 8000 2850
Connection ~ 7500 2550
Wire Wire Line
	7500 2550 7500 2850
$Comp
L power:GND #PWR08
U 1 1 615C09C8
P 8000 2850
F 0 "#PWR08" H 8000 2600 50  0001 C CNN
F 1 "GND" H 8005 2677 50  0000 C CNN
F 2 "" H 8000 2850 50  0001 C CNN
F 3 "" H 8000 2850 50  0001 C CNN
	1    8000 2850
	1    0    0    -1  
$EndComp
Text GLabel 8650 2250 2    50   Output ~ 0
GATE1
Text GLabel 8650 2150 2    50   Output ~ 0
GATE4
Text GLabel 8650 2050 2    50   Output ~ 0
GATE3
Text GLabel 8650 1950 2    50   Output ~ 0
GATE6
Text GLabel 8650 1750 2    50   Output ~ 0
GATE2
Text GLabel 8650 1850 2    50   Output ~ 0
GATE5
Wire Wire Line
	8500 1750 8650 1750
Wire Wire Line
	8500 1850 8650 1850
Wire Wire Line
	8500 1950 8650 1950
Wire Wire Line
	8500 2050 8650 2050
Wire Wire Line
	8500 2150 8650 2150
Wire Wire Line
	8500 2250 8650 2250
$Comp
L Triac_Thyristor:TIC126 Q1
U 1 1 615D9B93
P 4000 4900
F 0 "Q1" H 4088 4854 50  0000 L CNN
F 1 "TIC126" H 4088 4945 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4100 4825 50  0001 L CIN
F 3 "https://cdn-reichelt.de/documents/datenblatt/A400/TIC126.pdf" H 4000 4900 50  0001 L CNN
	1    4000 4900
	1    0    0    1   
$EndComp
$Comp
L Triac_Thyristor:TIC126 Q4
U 1 1 615DAE22
P 4000 5600
F 0 "Q4" H 4088 5554 50  0000 L CNN
F 1 "TIC126" H 4088 5645 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4100 5525 50  0001 L CIN
F 3 "https://cdn-reichelt.de/documents/datenblatt/A400/TIC126.pdf" H 4000 5600 50  0001 L CNN
	1    4000 5600
	1    0    0    1   
$EndComp
$Comp
L Triac_Thyristor:TIC126 Q3
U 1 1 615DBB90
P 4500 4900
F 0 "Q3" H 4588 4854 50  0000 L CNN
F 1 "TIC126" H 4588 4945 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4600 4825 50  0001 L CIN
F 3 "https://cdn-reichelt.de/documents/datenblatt/A400/TIC126.pdf" H 4500 4900 50  0001 L CNN
	1    4500 4900
	1    0    0    1   
$EndComp
$Comp
L Triac_Thyristor:TIC126 Q6
U 1 1 615DC9E1
P 4500 5600
F 0 "Q6" H 4588 5554 50  0000 L CNN
F 1 "TIC126" H 4588 5645 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4600 5525 50  0001 L CIN
F 3 "https://cdn-reichelt.de/documents/datenblatt/A400/TIC126.pdf" H 4500 5600 50  0001 L CNN
	1    4500 5600
	1    0    0    1   
$EndComp
$Comp
L Triac_Thyristor:TIC126 Q5
U 1 1 615DD8C1
P 5000 4900
F 0 "Q5" H 5088 4854 50  0000 L CNN
F 1 "TIC126" H 5088 4945 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5100 4825 50  0001 L CIN
F 3 "https://cdn-reichelt.de/documents/datenblatt/A400/TIC126.pdf" H 5000 4900 50  0001 L CNN
	1    5000 4900
	1    0    0    1   
$EndComp
$Comp
L Triac_Thyristor:TIC126 Q2
U 1 1 615DE98C
P 5000 5600
F 0 "Q2" H 5088 5554 50  0000 L CNN
F 1 "TIC126" H 5088 5645 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5100 5525 50  0001 L CIN
F 3 "https://cdn-reichelt.de/documents/datenblatt/A400/TIC126.pdf" H 5000 5600 50  0001 L CNN
	1    5000 5600
	1    0    0    1   
$EndComp
Wire Wire Line
	4000 4750 4000 4650
Wire Wire Line
	4000 4650 4500 4650
Wire Wire Line
	4500 4750 4500 4650
Connection ~ 4500 4650
Wire Wire Line
	4500 4650 5000 4650
Wire Wire Line
	5000 4750 5000 4650
Connection ~ 5000 4650
Wire Wire Line
	5000 4650 5550 4650
Wire Wire Line
	4000 5750 4000 5850
Wire Wire Line
	4500 5750 4500 5850
Wire Wire Line
	4000 5850 4500 5850
Connection ~ 4500 5850
Wire Wire Line
	4500 5850 5000 5850
Wire Wire Line
	5000 5750 5000 5850
Connection ~ 5000 5850
Wire Wire Line
	5000 5850 5550 5850
Text GLabel 3400 5400 0    50   Input ~ 0
FASE_C
Wire Wire Line
	3400 5250 4500 5250
Wire Wire Line
	3400 5100 4000 5100
Wire Wire Line
	4000 5100 4000 5050
Wire Wire Line
	5000 5450 5000 5400
Wire Wire Line
	4500 5450 4500 5250
Connection ~ 4500 5250
Wire Wire Line
	4500 5250 4500 5050
Wire Wire Line
	4000 5450 4000 5100
Connection ~ 4000 5100
Wire Wire Line
	3400 5400 5000 5400
Connection ~ 5000 5400
Wire Wire Line
	5000 5400 5000 5050
Text Label 3600 5100 0    50   ~ 0
FA
Text Label 3600 5250 0    50   ~ 0
FB
Text Label 2400 2550 0    50   ~ 0
FA
Text Label 2400 2150 0    50   ~ 0
FB
Wire Wire Line
	6050 1550 5750 1550
Text GLabel 5750 1550 0    50   Input ~ 0
ALPHA
Text Notes 5250 1450 0    50   ~ 0
From Arduino DA:\n0 .. 2.5V\n0 .. 180°
$Comp
L Device:R R3
U 1 1 6164F596
P 7800 5550
F 0 "R3" V 7593 5550 50  0000 C CNN
F 1 "470R" V 7684 5550 50  0000 C CNN
F 2 "" V 7730 5550 50  0001 C CNN
F 3 "~" H 7800 5550 50  0001 C CNN
	1    7800 5550
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 616500B1
P 8000 5750
F 0 "R4" H 8070 5796 50  0000 L CNN
F 1 "1K" H 8070 5705 50  0000 L CNN
F 2 "" V 7930 5750 50  0001 C CNN
F 3 "~" H 8000 5750 50  0001 C CNN
	1    8000 5750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BD135 Q7
U 1 1 6165113C
P 8250 5550
F 0 "Q7" H 8442 5596 50  0000 L CNN
F 1 "BD135" H 8442 5505 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-126-3_Vertical" H 8450 5475 50  0001 L CIN
F 3 "http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00001225.pdf" H 8250 5550 50  0001 L CNN
	1    8250 5550
	1    0    0    -1  
$EndComp
$Comp
L Transformer:PA0184NL T2
U 1 1 61654E9F
P 9000 5100
F 0 "T2" H 9000 5481 50  0000 C CNN
F 1 "PA0184NL" H 9000 5390 50  0000 C CNN
F 2 "Transformer_SMD:Pulse_PA2007NL" H 9000 5100 50  0001 C CNN
F 3 "https://productfinder.pulseeng.com/products/datasheets/SPM2007_61.pdf" H 8700 5100 50  0001 C CNN
	1    9000 5100
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148W D4
U 1 1 61658442
P 8350 5100
F 0 "D4" V 8304 5180 50  0000 L CNN
F 1 "1N4148W" V 8395 5180 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 8350 4925 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 8350 5100 50  0001 C CNN
	1    8350 5100
	0    1    1    0   
$EndComp
$Comp
L Diode:DZ2S150X0L D3
U 1 1 61659F40
P 8350 4800
F 0 "D3" V 8304 4880 50  0000 L CNN
F 1 "ZENER 12V" V 8395 4880 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 8350 4625 50  0001 C CNN
F 3 "https://industrial.panasonic.com/content/data/SC/ds/ds4/DZ2S15000L_E.pdf" H 8350 4800 50  0001 C CNN
	1    8350 4800
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 6165CBF7
P 8350 4400
F 0 "R5" H 8420 4446 50  0000 L CNN
F 1 "18R 5W" H 8420 4355 50  0000 L CNN
F 2 "" V 8280 4400 50  0001 C CNN
F 3 "~" H 8350 4400 50  0001 C CNN
	1    8350 4400
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D5
U 1 1 6165E426
P 9350 4900
F 0 "D5" H 9350 4683 50  0000 C CNN
F 1 "1N4007" H 9350 4774 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 9350 4725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 9350 4900 50  0001 C CNN
	1    9350 4900
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 6165FACB
P 9500 5100
F 0 "R6" H 9570 5146 50  0000 L CNN
F 1 "2K2" H 9570 5055 50  0000 L CNN
F 2 "" V 9430 5100 50  0001 C CNN
F 3 "~" H 9500 5100 50  0001 C CNN
	1    9500 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 6167E405
P 8350 5900
F 0 "#PWR011" H 8350 5650 50  0001 C CNN
F 1 "GND" H 8355 5727 50  0000 C CNN
F 2 "" H 8350 5900 50  0001 C CNN
F 3 "" H 8350 5900 50  0001 C CNN
	1    8350 5900
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR010
U 1 1 6167FCFA
P 8350 4250
F 0 "#PWR010" H 8350 4100 50  0001 C CNN
F 1 "+12V" H 8365 4423 50  0000 C CNN
F 2 "" H 8350 4250 50  0001 C CNN
F 3 "" H 8350 4250 50  0001 C CNN
	1    8350 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 616814C3
P 8000 4550
F 0 "C3" H 8115 4596 50  0000 L CNN
F 1 "100nF" H 8115 4505 50  0000 L CNN
F 2 "" H 8038 4400 50  0001 C CNN
F 3 "~" H 8000 4550 50  0001 C CNN
	1    8000 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 4250 8000 4250
Wire Wire Line
	8000 4250 8000 4400
Connection ~ 8350 4250
$Comp
L power:GND #PWR09
U 1 1 61684E0F
P 8000 4700
F 0 "#PWR09" H 8000 4450 50  0001 C CNN
F 1 "GND" H 8005 4527 50  0000 C CNN
F 2 "" H 8000 4700 50  0001 C CNN
F 3 "" H 8000 4700 50  0001 C CNN
	1    8000 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 4650 8350 4600
Wire Wire Line
	8350 5350 8350 5300
Wire Wire Line
	8350 5300 8800 5300
Connection ~ 8350 5300
Wire Wire Line
	8350 5300 8350 5250
Wire Wire Line
	8350 4600 8800 4600
Wire Wire Line
	8800 4600 8800 4900
Connection ~ 8350 4600
Wire Wire Line
	8350 4600 8350 4550
Wire Wire Line
	9200 5300 9500 5300
Wire Wire Line
	9500 5300 9500 5250
Connection ~ 9500 5300
Wire Wire Line
	9500 5300 9750 5300
Wire Wire Line
	9500 4900 9750 4900
Wire Wire Line
	9500 4950 9500 4900
Connection ~ 9500 4900
Wire Wire Line
	8050 5550 8000 5550
Wire Wire Line
	8000 5600 8000 5550
Connection ~ 8000 5550
Wire Wire Line
	8000 5550 7950 5550
Wire Wire Line
	8000 5900 8350 5900
Wire Wire Line
	8350 5900 8350 5750
Connection ~ 8350 5900
Wire Wire Line
	7650 5550 7550 5550
Text GLabel 7550 5550 0    50   Input ~ 0
GATEx
Text Label 9750 4900 0    50   ~ 0
Qx_G
Text Label 9750 5300 0    50   ~ 0
Qx_K
Wire Notes Line
	10000 4000 10000 6200
Wire Notes Line
	10000 6200 7200 6200
Wire Notes Line
	7200 6200 7200 4000
Wire Notes Line
	7200 4000 10000 4000
Text Notes 7300 4250 0    100  ~ 0
6x
Wire Notes Line
	5800 4450 5800 6050
Wire Notes Line
	5800 6050 2750 6050
Wire Notes Line
	2750 6050 2750 4450
Wire Notes Line
	2750 4450 5800 4450
Text Notes 2900 4400 0    100  ~ 0
Power
Text Notes 7250 3950 0    100  ~ 0
Gate Driver (amplifier and isolator)
Connection ~ 8000 2850
Text Notes 3150 2350 0    50   ~ 0
9V / 10mA
Text Notes 2550 2350 0    50   ~ 0
220V
Wire Notes Line
	2550 2650 2550 2000
Wire Notes Line
	2550 2000 2350 2000
Wire Notes Line
	2350 2000 2350 2650
Wire Notes Line
	2350 2650 2550 2650
Text Notes 1350 2450 0    50   ~ 10
Attention here:\nLM311 in open collector\ninverts signal, so\nthe phases are inverted!!
Connection ~ 3700 2550
Wire Wire Line
	3350 2550 3700 2550
$EndSCHEMATC
