# Raspberry LCD
# Hardware
* Raspberry PI (version 2 was used)
* EA DIGS104-A

The devices were connected via **SPI**.

## Raspberry

SPI-GPIOs at the Raspberry:
* GPIO10 MOSI
* GPIO9  MISO
* GPIO11 SCLK
* GPIO8  CE0

Additional commands:
* GPIO18	LCD backlight control

## Display

EA DOGS104-A including *SSD1803A* controller

# Software

Load the kernel module `sudo modprobe spi_bcm2835`  .

In the folder */etc/udev/rules.d/* generate a file named **51-i2c.rules**.
With the following content: `SUBSYSTEM=="spidev", GROUP="users", MODE="0660"`  

After restarting the service, everything is prepared:
`sudo service udev restart` 

## Dependencies
* build-essentials
* cmake

## Build
Go into the bulid folder and use ``cmake`` and ``make`` to build the tool.

As shown here:
```
cd build
cmake ../
make
```

# Sources
* [SPI at Raspberry (in German)](http://www.netzmafia.de/skripten/hardware/RasPi/RasPi_SPI.html)
* [GPIOs of Raspberry](https://pinout.xyz/pinout/pin19_gpio10)
* [LCD Hardware (distributor)](https://www.reichelt.de/DOG-LCD-Module/EA-DOGS104B-A/3/index.html?ACTION=3&LA=2&ARTICLE=156569&GROUPID=3007&artnr=EA+DOGS104B-A&SEARCH=%252A)
