# FC980C Controller
Design modifications are based on parent [project](https://github.com/wlhlm/fc980c-controller).  

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

## Thank you
Thank you to [wlhlm](https://github.com/wlhlm) for all the work that went into this.  
