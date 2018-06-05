# TrueOrFalseGame

## Overview

Test Your knowledge in the TrueOrFalseGame. Chances are 50/50. Are You smart enough to answer all the questions?

## Tools

To make it work, we used STM32F4 board as a heart and brain of the project. Additional peripherals are LCD, display, SD card reader, RGB and buttons module. Code was written and compiled by System Workbench for STM32.

## How to run

**PINS:**

**SD:**<br />
PB13 -> SCK <br />
PB14 -> MISO <br />
PB15 -> MOSI <br />
PB11 -> CHIP SELECT <br />

**LCD:** <br />
GND	-> GND <br />	
VCC	-> +5V <br />				 
V0	-> GND <br />
RS	-> PB2 <br />				
RW	-> GND	<br />			
E	-> PB7	<br />			
D0		-		<br />	
D1		-			<br />	
D2		-			<br />	
D3		-			<br />	
D4	-> PC12		<br />	
D5	-> PC13		<br />	
D6 -> PB12		<br />	
D7 -> PB13		<br />	
A	-> +5V		<br />
K	-> GND		<br />		

**Buttons:** <br />
K7 -> PA1 <br />
K3 -> PA2 <br />
G -> GND <br />

**Dislpay:** <br />
1 -> PE1 <br />
2 - <br />
3 -> PE0 <br />
4 -> PE2 <br />
5 -> PE5 <br />
6 -> PE6 <br />
7 -> +3V <br />
8 -> PE4 <br />

## How to compile

We recommend System Worbench for STM32.

## Future improvements

- adding more questions <br />
- claryfing the code <br />

## Attributions

We used FatFs library.

## License

*MIT*

## Credits

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Contractors: KK, SJ

Supervisor: Tomasz Mańkowski
