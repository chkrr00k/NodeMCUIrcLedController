# NodeMCUIrcLedController
A very simple implementation of the basic of the IRC protocol on a NodeMCU ESP8266. When a user in the selected channel writes ".on" the led connected to the NodeMCU will power on!  

## Schematics
R1 is a Resistor to protect the Led  
LED is a led, ofc (in my case it's blue!)  
```
            R1      LED
     +---/\/\/\/\---(/)---+
 ____|____________________|_______________________________
| D0 D1  D2  D3  D4  3V  GND D5  D6  D7  D8 Rx Tx  GND 3V  |
|                                                         _|_
|                                                        |___| USB
| A0 RSV RSV SD3 SD2 SD2 CMD SD0 CLK GND 3V EN RST GND Vin |
|__________________________________________________________|
```
