# FC980C Controller
Design modifications are based on parent [project](https://github.com/wlhlm/fc980c-controller).  

Similar concept to Hasu 980c controller but it is a nice upgrade in processing limitations vs the Atmega32u4.

Related project [USB-C Daughterboard](https://github.com/davek184/980_Usb_C_Daughterboard)

![Image](https://i.imgur.com/SFc11gN.jpg)
![ImageInstalled](https://i.imgur.com/FoyMTGV.jpg)

## Changes
* Added USB SH Connector
* Added USB Molex EZ-Mate connector
* Added RGB Underglow support (Norbauer Heavy-9 is the only case I know of that could take advantage of this)
* Added MegaMan logo
* Altered Boot0 so it can be shorted with tweasers for those who don't want to solder a switch
* Altered ISP header

## Firmware
* [Precompiled Firmware](/firmware)
* Can also be compiled into QMK or VIAL firmware yourself using files in the [firmware](/firmware/fc980c) directory

Firmware can be flashed with QMK Toolbox.  To get into bootloader mode short the BootO pins (or press and hold the reset switch) **WHILE connecting the USB cable**

## Manufacturing
* Files are set up for JLCPCB.  
* Select Specify a location for Remove Order Number (that will put it in a set location)
* Choose PCB Assembly
  * Assemble top Side
  * Tooling holes Added by customer
  * Confirm parts placement Yes
* Optional Parts
  * J1 The USB Molex EZ-mate connector, is optional and can be deselected to save some money
  * J4 The USB SH connector, is optional and can be deselected to save some money
  * J5 The RGB underglow connector, is optional and can be deselected to save some money

**Note the keyboard connector is not available at this time to be assembled.  It must be soldered by yourself!**

Hirose part number DF14-20P-1.25H(52).  Mouser: https://www.mouser.com/ProductDetail/798-DF1420P125H52

_(This is the same keyboard connector the FC660c uses)_

## Thank you
Thank you to [wlhlm](https://github.com/wlhlm) for all the work that went into this.  
