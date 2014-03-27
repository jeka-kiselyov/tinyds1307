tinyds1307
==========

Library for the ATtiny85 on Arduino for DS1307. With RAM support.

#### License ####
The MIT License (MIT)

#### Dependencies ####
*   [TinyWireM](http://playground.arduino.cc/Code/USIi2c ) (TinyWireM.zip) 

#### Resources ####
*   [DS1307 datasheet](http://datasheets.maximintegrated.com/en/ds/DS1307.pdf)
*   [ATtiny85 datasheet](http://www.atmel.com/images/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf)
*   [I2C Master and Slave on the ATtiny85](http://playground.arduino.cc/Code/USIi2c)
*   [DS1307 for Arduino](https://code.google.com/p/ds1307new/)
*   [DS1307RTS](http://www.pjrc.com/teensy/td_libs_DS1307RTC.html)

#### Setup ####
*   ATtiny Pin 5 = SDA 
*   ATtiny Pin 7 = SCL
#####Note:#####
It's important to use pullups on SDA & SCL. 4k7 resistors from SDA to VCC and from SCL to VCC are good. (anything from 1k to 10k is good).

#### Usage ####
*   insude setup():
```
    TinyWireM.begin();                    // initialize I2C lib
    tinyrtc.begin();                      // inititalize DS1307
    if (!tinyrtc.isrunning()) {           // if this is first run (or there's no battery on DS1307)
        tinyrtc.adjust(2014,3,27,21,13,59); // set up time Y, M, D, HH, MM, SS
    }
```
*   inside loop():
```
    // get date/date:
    tinyrtc.read();     // read data from DS1307 to get fresh/actual values
    unsigned char seconds = tinyrtc.second(); // 0 - 59
    unsigned char minutes = tinyrtc.minute(); // 0 - 59
    unsigned char hours   = tinyrtc.hour();   // 0 - 23
    unsigned char day     = tinyrtc.day();    // 1 - 31
    unsigned char month   = tinyrtc.month();  // 1 - 12
    unsigned short year   = tinyrtc.year();   // 2000 - ...

    // get data from DS1307 RAM:
    tinyrtc.read_ram();   /// get fresh/actual data from DS1307 RAM
    tinyrtc.ram[0] ... tinyrtc.ram[55] - /// data ( unsigned char ram[DS1307_RAM_SIZE]; )

    // save data to DS1307 RAM:
    tinyrtc.ram[0] = 32; ... tinyrtc.ram[55] = 150; /// 56 bytes
    tinyrtc.write_ram();     /// commit :) 
```

####Notes####
*   If your project needs less bytes of RAM - feel free to lower DS1307_RAM_SIZE in TinyDS1307.h This will save you few bytes of memory and improve speed of read_ram() and write_ram() methods.
