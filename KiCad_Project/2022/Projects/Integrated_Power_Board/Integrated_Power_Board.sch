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
L Filter:BNX025 FL1
U 1 1 61E9826B
P 4500 2450
F 0 "FL1" H 4500 2775 50  0000 C CNN
F 1 "BNX025" H 4500 2684 50  0000 C CNN
F 2 "Library:FIL_BNX016-01" H 4500 2250 50  0001 C CNN
F 3 "https://www.murata.com/en-us/products/productdetail.aspx?cate=luNoiseSupprFilteBlockType&partno=BNX025H01%23" V 4475 2425 50  0001 C CNN
	1    4500 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 61E9D1C6
P 5300 2500
F 0 "C2" H 5418 2546 50  0000 L CNN
F 1 "CP" H 5418 2455 50  0000 L CNN
F 2 "Capacitor_THT:C_Radial_D16.0mm_H25.0mm_P7.50mm" H 5338 2350 50  0001 C CNN
F 3 "~" H 5300 2500 50  0001 C CNN
	1    5300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2350 5300 2350
Wire Wire Line
	4900 2550 4900 2650
Wire Wire Line
	4900 2650 5300 2650
Connection ~ 5300 2350
$Comp
L Device:D D3
U 1 1 61EAA1B2
P 9350 2350
F 0 "D3" H 9350 2133 50  0000 C CNN
F 1 "D" H 9350 2224 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P7.62mm_Horizontal" H 9350 2350 50  0001 C CNN
F 3 "~" H 9350 2350 50  0001 C CNN
	1    9350 2350
	-1   0    0    1   
$EndComp
$Comp
L Device:C C4
U 1 1 61ECBA50
P 8850 2650
F 0 "C4" H 8965 2696 50  0000 L CNN
F 1 "C" H 8965 2605 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 8888 2500 50  0001 C CNN
F 3 "~" H 8850 2650 50  0001 C CNN
	1    8850 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 61ECFE45
P 5900 2500
F 0 "C3" H 6015 2546 50  0000 L CNN
F 1 "C" H 6015 2455 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 5938 2350 50  0001 C CNN
F 3 "~" H 5900 2500 50  0001 C CNN
	1    5900 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2350 5900 2350
Connection ~ 5900 2350
Wire Wire Line
	5900 2350 6100 2350
Wire Wire Line
	5900 2650 5900 3150
Wire Wire Line
	5300 2650 5900 2650
Connection ~ 5300 2650
Connection ~ 5900 2650
$Comp
L Device:R R4
U 1 1 61ED432C
P 6250 2550
F 0 "R4" H 6320 2596 50  0000 L CNN
F 1 "R" H 6320 2505 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6180 2550 50  0001 C CNN
F 3 "~" H 6250 2550 50  0001 C CNN
	1    6250 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6100 2550 6100 2350
Connection ~ 6100 2350
Wire Wire Line
	6100 2350 6400 2350
NoConn ~ 8000 2750
Wire Wire Line
	5900 3150 6100 3150
Wire Wire Line
	6100 3150 6100 3050
Connection ~ 6100 3150
Wire Wire Line
	6100 3150 8600 3150
Wire Wire Line
	6100 2650 6100 2550
Connection ~ 6100 2550
Wire Wire Line
	8850 2350 8850 2500
$Comp
L Device:R R6
U 1 1 61EE2976
P 9150 2650
F 0 "R6" H 9220 2696 50  0000 L CNN
F 1 "R" H 9220 2605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9080 2650 50  0001 C CNN
F 3 "~" H 9150 2650 50  0001 C CNN
	1    9150 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 3150 9150 3150
Wire Wire Line
	9150 3150 9150 2800
Wire Wire Line
	8850 2350 9150 2350
Wire Wire Line
	9150 2500 9150 2350
Connection ~ 9150 2350
Wire Wire Line
	9150 2350 9200 2350
$Comp
L Device:R_POT_TRIM_US RV2
U 1 1 61EE7113
P 8250 2650
F 0 "RV2" V 8175 2725 50  0000 R CNN
F 1 "R_POT_TRIM_US" V 8450 2950 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 8250 2650 50  0001 C CNN
F 3 "~" H 8250 2650 50  0001 C CNN
	1    8250 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	8850 2800 8850 3150
$Comp
L Device:R R5
U 1 1 61EF0CD5
P 8600 2800
F 0 "R5" H 8670 2846 50  0000 L CNN
F 1 "R" H 8670 2755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8530 2800 50  0001 C CNN
F 3 "~" H 8600 2800 50  0001 C CNN
	1    8600 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2650 8450 2650
Wire Wire Line
	8450 2650 8450 2800
Wire Wire Line
	8450 2800 8250 2800
Connection ~ 8450 2650
Wire Wire Line
	8000 2950 8600 2950
Wire Wire Line
	8450 2650 8600 2650
Connection ~ 8600 2950
Wire Wire Line
	8000 2650 8100 2650
Wire Wire Line
	8600 3150 8600 2950
Connection ~ 8850 2350
Wire Wire Line
	8000 2350 8850 2350
Wire Wire Line
	8000 2550 8850 2350
Wire Wire Line
	8600 3150 8850 3150
Connection ~ 8600 3150
Connection ~ 8850 3150
Wire Wire Line
	9150 3150 9550 3150
Connection ~ 9150 3150
Wire Wire Line
	9500 2350 9550 2350
$Comp
L power:GND1 #PWR017
U 1 1 61EBE4FF
P 9550 3150
F 0 "#PWR017" H 9550 2900 50  0001 C CNN
F 1 "GND1" H 9555 2977 50  0000 C CNN
F 2 "" H 9550 3150 50  0001 C CNN
F 3 "" H 9550 3150 50  0001 C CNN
	1    9550 3150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR016
U 1 1 61EBF0D6
P 9550 2350
F 0 "#PWR016" H 9550 2200 50  0001 C CNN
F 1 "+5V" V 9565 2478 50  0000 L CNN
F 2 "" H 9550 2350 50  0001 C CNN
F 3 "" H 9550 2350 50  0001 C CNN
	1    9550 2350
	0    1    1    0   
$EndComp
$Comp
L Device:Battery BT1
U 1 1 61EBFC23
P 1575 2550
F 0 "BT1" H 1683 2596 50  0000 L CNN
F 1 "Battery" H 1683 2505 50  0000 L CNN
F 2 "Connector_JST:JST_VH_B2P-VH-B_1x02_P3.96mm_Vertical" V 1575 2610 50  0001 C CNN
F 3 "~" V 1575 2610 50  0001 C CNN
	1    1575 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse F1
U 1 1 61EC72DA
P 1875 2350
F 0 "F1" V 1678 2350 50  0000 C CNN
F 1 "Fuse" V 1769 2350 50  0000 C CNN
F 2 "Library:fuse_socket" V 1805 2350 50  0001 C CNN
F 3 "~" H 1875 2350 50  0001 C CNN
	1    1875 2350
	0    1    1    0   
$EndComp
$Comp
L Device:Varistor RV1
U 1 1 61EC95F5
P 3650 2500
F 0 "RV1" H 3753 2546 50  0000 L CNN
F 1 "Varistor" H 3753 2455 50  0000 L CNN
F 2 "" V 3580 2500 50  0001 C CNN
F 3 "~" H 3650 2500 50  0001 C CNN
	1    3650 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1575 2350 1725 2350
Wire Wire Line
	3650 2350 3900 2350
Wire Wire Line
	4100 2550 4100 2650
Wire Wire Line
	4100 2650 3650 2650
Wire Wire Line
	3650 2750 3650 2650
Connection ~ 3650 2650
$Comp
L power:GND #PWR01
U 1 1 61ED0CD7
P 1575 2750
F 0 "#PWR01" H 1575 2500 50  0001 C CNN
F 1 "GND" H 1580 2577 50  0000 C CNN
F 2 "" H 1575 2750 50  0001 C CNN
F 3 "" H 1575 2750 50  0001 C CNN
	1    1575 2750
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR05
U 1 1 61ED14A8
P 3900 2350
F 0 "#PWR05" H 3900 2200 50  0001 C CNN
F 1 "+12V" H 3915 2523 50  0000 C CNN
F 2 "" H 3900 2350 50  0001 C CNN
F 3 "" H 3900 2350 50  0001 C CNN
	1    3900 2350
	1    0    0    -1  
$EndComp
Connection ~ 3900 2350
Wire Wire Line
	3900 2350 4100 2350
$Comp
L Device:Voltmeter_DC MES1
U 1 1 61ED4B62
P 2775 2550
F 0 "MES1" H 2875 2450 50  0000 L CNN
F 1 "Voltmeter_DC" H 2525 2250 50  0000 L CNN
F 2 "Library:voltage_counter" V 2775 2650 50  0001 C CNN
F 3 "~" V 2775 2650 50  0001 C CNN
	1    2775 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2775 2350 2975 2350
Connection ~ 2775 2350
Connection ~ 3650 2350
Connection ~ 1575 2750
Text GLabel 2775 2150 1    50   Input ~ 0
Voltage
Wire Wire Line
	2775 2150 2775 2350
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 61EF0035
P 5875 3625
F 0 "J2" V 5839 3437 50  0000 R CNN
F 1 "Conn_01x02" V 5748 3437 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 5875 3625 50  0001 C CNN
F 3 "~" H 5875 3625 50  0001 C CNN
	1    5875 3625
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 61EF3E59
P 8700 3650
F 0 "J5" V 8664 3462 50  0000 R CNN
F 1 "Conn_01x02" V 8573 3462 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 8700 3650 50  0001 C CNN
F 3 "~" H 8700 3650 50  0001 C CNN
	1    8700 3650
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 61EF4C98
P 9450 3650
F 0 "J6" V 9414 3462 50  0000 R CNN
F 1 "Conn_01x02" V 9323 3462 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 9450 3650 50  0001 C CNN
F 3 "~" H 9450 3650 50  0001 C CNN
	1    9450 3650
	0    -1   -1   0   
$EndComp
Connection ~ 2775 2750
$Comp
L power:+12V #PWR07
U 1 1 61EE4D28
P 5875 3825
F 0 "#PWR07" H 5875 3675 50  0001 C CNN
F 1 "+12V" H 5950 4000 50  0000 C CNN
F 2 "" H 5875 3825 50  0001 C CNN
F 3 "" H 5875 3825 50  0001 C CNN
	1    5875 3825
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 61EE840C
P 5975 3825
F 0 "#PWR08" H 5975 3575 50  0001 C CNN
F 1 "GND" H 6075 3650 50  0000 C CNN
F 2 "" H 5975 3825 50  0001 C CNN
F 3 "" H 5975 3825 50  0001 C CNN
	1    5975 3825
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 61EEBF37
P 6625 3625
F 0 "J3" V 6589 3437 50  0000 R CNN
F 1 "Conn_01x02" V 6498 3437 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 6625 3625 50  0001 C CNN
F 3 "~" H 6625 3625 50  0001 C CNN
	1    6625 3625
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR09
U 1 1 61EEBF3D
P 6625 3825
F 0 "#PWR09" H 6625 3675 50  0001 C CNN
F 1 "+12V" H 6700 4000 50  0000 C CNN
F 2 "" H 6625 3825 50  0001 C CNN
F 3 "" H 6625 3825 50  0001 C CNN
	1    6625 3825
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 61EEBF43
P 6725 3825
F 0 "#PWR010" H 6725 3575 50  0001 C CNN
F 1 "GND" H 6825 3650 50  0000 C CNN
F 2 "" H 6725 3825 50  0001 C CNN
F 3 "" H 6725 3825 50  0001 C CNN
	1    6725 3825
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 61EEE7BE
P 7350 3625
F 0 "J4" V 7314 3437 50  0000 R CNN
F 1 "Conn_01x02" V 7223 3437 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 7350 3625 50  0001 C CNN
F 3 "~" H 7350 3625 50  0001 C CNN
	1    7350 3625
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR011
U 1 1 61EEE7C4
P 7350 3825
F 0 "#PWR011" H 7350 3675 50  0001 C CNN
F 1 "+12V" H 7425 4000 50  0000 C CNN
F 2 "" H 7350 3825 50  0001 C CNN
F 3 "" H 7350 3825 50  0001 C CNN
	1    7350 3825
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 61EEE7CA
P 7450 3825
F 0 "#PWR012" H 7450 3575 50  0001 C CNN
F 1 "GND" H 7550 3650 50  0000 C CNN
F 2 "" H 7450 3825 50  0001 C CNN
F 3 "" H 7450 3825 50  0001 C CNN
	1    7450 3825
	1    0    0    -1  
$EndComp
$Comp
L power:GND1 #PWR014
U 1 1 61EEFCBF
P 8800 3850
F 0 "#PWR014" H 8800 3600 50  0001 C CNN
F 1 "GND1" H 8925 3675 50  0000 C CNN
F 2 "" H 8800 3850 50  0001 C CNN
F 3 "" H 8800 3850 50  0001 C CNN
	1    8800 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND1 #PWR018
U 1 1 61EF1431
P 9550 3850
F 0 "#PWR018" H 9550 3600 50  0001 C CNN
F 1 "GND1" H 9650 3675 50  0000 C CNN
F 2 "" H 9550 3850 50  0001 C CNN
F 3 "" H 9550 3850 50  0001 C CNN
	1    9550 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 61EF2328
P 8700 3850
F 0 "#PWR013" H 8700 3700 50  0001 C CNN
F 1 "+5V" H 8725 4025 50  0000 L CNN
F 2 "" H 8700 3850 50  0001 C CNN
F 3 "" H 8700 3850 50  0001 C CNN
	1    8700 3850
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 61EF49C8
P 9450 3850
F 0 "#PWR015" H 9450 3700 50  0001 C CNN
F 1 "+5V" H 9450 4025 50  0000 L CNN
F 2 "" H 9450 3850 50  0001 C CNN
F 3 "" H 9450 3850 50  0001 C CNN
	1    9450 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	1575 2750 2100 2750
Wire Wire Line
	2025 2350 2100 2350
$Comp
L Switch:SW_SPST SW2
U 1 1 61EDE86A
P 6100 2850
F 0 "SW2" V 6054 2948 50  0000 L CNN
F 1 "SW_SPST" V 6145 2948 50  0000 L CNN
F 2 "Library:toggleswitch" H 6100 2850 50  0001 C CNN
F 3 "~" H 6100 2850 50  0001 C CNN
	1    6100 2850
	0    1    1    0   
$EndComp
$Comp
L Converter_DCDC:OKL-T_6-W12N-C U2
U 1 1 61EADD40
P 7200 2650
F 0 "U2" H 7200 3215 50  0000 C CNN
F 1 "OKL-T_6-W12N-C" H 7200 3124 50  0000 C CNN
F 2 "Library:DCDC-murata-6A" H 6750 3100 50  0001 L BNN
F 3 "" H 7200 2650 50  0001 L BNN
	1    7200 2650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW1
U 1 1 62001AB7
P 3175 2350
F 0 "SW1" V 3129 2448 50  0000 L CNN
F 1 "SW_SPST" V 3220 2448 50  0000 L CNN
F 2 "" H 3175 2350 50  0001 C CNN
F 3 "~" H 3175 2350 50  0001 C CNN
	1    3175 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Shockley D1
U 1 1 62006518
P 2100 2550
F 0 "D1" V 2054 2630 50  0000 L CNN
F 1 "D_Shockley" V 2145 2630 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 2100 2550 50  0001 C CNN
F 3 "~" H 2100 2550 50  0001 C CNN
	1    2100 2550
	0    1    1    0   
$EndComp
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U1
U 1 1 62009351
P 2325 4025
F 0 "U1" H 1796 4071 50  0000 R CNN
F 1 "ATtiny85-20PU" H 1796 3980 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 2325 4025 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 2325 4025 50  0001 C CNN
	1    2325 4025
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2400 2100 2350
Connection ~ 2100 2350
Wire Wire Line
	2100 2700 2100 2750
Connection ~ 2100 2750
$Comp
L power:GND1 #PWR03
U 1 1 62012FF3
P 2325 4625
F 0 "#PWR03" H 2325 4375 50  0001 C CNN
F 1 "GND1" H 2330 4452 50  0000 C CNN
F 2 "" H 2325 4625 50  0001 C CNN
F 3 "" H 2325 4625 50  0001 C CNN
	1    2325 4625
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 62019AD6
P 3475 2550
F 0 "C1" H 3593 2596 50  0000 L CNN
F 1 "CP" H 3593 2505 50  0000 L CNN
F 2 "Capacitor_THT:C_Radial_D16.0mm_H25.0mm_P7.50mm" H 3513 2400 50  0001 C CNN
F 3 "~" H 3475 2550 50  0001 C CNN
	1    3475 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2350 2775 2350
Wire Wire Line
	2100 2750 2775 2750
Wire Wire Line
	3375 2350 3475 2350
Wire Wire Line
	3475 2350 3475 2400
Connection ~ 3475 2350
Wire Wire Line
	3475 2350 3650 2350
Wire Wire Line
	2775 2750 3475 2750
$Comp
L power:+5V #PWR02
U 1 1 6201F98D
P 2325 3425
F 0 "#PWR02" H 2325 3275 50  0001 C CNN
F 1 "+5V" H 2340 3598 50  0000 C CNN
F 2 "" H 2325 3425 50  0001 C CNN
F 3 "" H 2325 3425 50  0001 C CNN
	1    2325 3425
	1    0    0    -1  
$EndComp
Text GLabel 4125 3550 1    50   Input ~ 0
Voltage
$Comp
L Device:R R2
U 1 1 62011B4B
P 4125 3775
F 0 "R2" H 4195 3821 50  0000 L CNN
F 1 "R" H 4195 3730 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4055 3775 50  0001 C CNN
F 3 "~" H 4125 3775 50  0001 C CNN
	1    4125 3775
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 62012DE4
P 4125 4075
F 0 "R3" H 4195 4121 50  0000 L CNN
F 1 "R" H 4195 4030 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4055 4075 50  0001 C CNN
F 3 "~" H 4125 4075 50  0001 C CNN
	1    4125 4075
	1    0    0    -1  
$EndComp
Connection ~ 4125 3925
Wire Wire Line
	4125 3625 4125 3550
$Comp
L power:GND #PWR06
U 1 1 62026D30
P 4125 4275
F 0 "#PWR06" H 4125 4025 50  0001 C CNN
F 1 "GND" H 4130 4102 50  0000 C CNN
F 2 "" H 4125 4275 50  0001 C CNN
F 3 "" H 4125 4275 50  0001 C CNN
	1    4125 4275
	1    0    0    -1  
$EndComp
Wire Wire Line
	2925 3925 4125 3925
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 6202E790
P 3350 3725
F 0 "J1" H 3430 3717 50  0000 L CNN
F 1 "Conn_01x02" H 3430 3626 50  0000 L CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 3350 3725 50  0001 C CNN
F 3 "~" H 3350 3725 50  0001 C CNN
	1    3350 3725
	1    0    0    -1  
$EndComp
Wire Wire Line
	2925 3725 3150 3725
Wire Wire Line
	2925 3825 3150 3825
Text Label 3000 3725 0    50   ~ 0
TX
Text Label 3000 3825 0    50   ~ 0
RX
Wire Wire Line
	3475 2700 3475 2750
Connection ~ 3475 2750
Wire Wire Line
	3475 2750 3650 2750
NoConn ~ 2925 4225
NoConn ~ 2925 4125
$Comp
L Device:LED D2
U 1 1 62036027
P 3450 4550
F 0 "D2" V 3489 4432 50  0000 R CNN
F 1 "LED" V 3398 4432 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm_Clear" H 3450 4550 50  0001 C CNN
F 3 "~" H 3450 4550 50  0001 C CNN
	1    3450 4550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 6203AED7
P 3450 4200
F 0 "R1" H 3520 4246 50  0000 L CNN
F 1 "R" H 3520 4155 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3380 4200 50  0001 C CNN
F 3 "~" H 3450 4200 50  0001 C CNN
	1    3450 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4125 4275 4125 4225
Wire Wire Line
	3450 4400 3450 4350
Wire Wire Line
	3450 4050 3450 4025
Wire Wire Line
	3450 4025 2925 4025
$Comp
L power:GND #PWR04
U 1 1 62041296
P 3450 4750
F 0 "#PWR04" H 3450 4500 50  0001 C CNN
F 1 "GND" H 3455 4577 50  0000 C CNN
F 2 "" H 3450 4750 50  0001 C CNN
F 3 "" H 3450 4750 50  0001 C CNN
	1    3450 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4750 3450 4700
$EndSCHEMATC
