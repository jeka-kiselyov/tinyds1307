// Scriptname : TinyDS1307.h
// Author     : Evgeniy Kiselyov
// Contact    : jeka911@gmail.com
// Date       : 2014-27-03
// Version    : 0.00001
// License    : The MIT License
// 
// Description: headers for TinyDS1307.cpp

#ifndef _TINYDS1307_H_
#define _TINYDS1307_H_

#include "Arduino.h"
#include "TinyWireM.h"

// if your project needs less bytes of RAM - feel free to lower DS1307_RAM_SIZE. 
// It will save you few bytes of memory and add speed for read_ram() and write_ram();
#define DS1307_RAM_SIZE 56  
#define DS1307_ADDRESS 0x68

class TINYDS1307 {
public:
    static bool begin(void);
    bool adjust(unsigned short year, unsigned char month, unsigned char day, unsigned char hour = 0, unsigned char min = 0, unsigned char sec = 0);
    bool isrunning(void);
    bool read();

    bool read_ram(void);
    bool write_ram(void);

    unsigned short year() const       { return y; }
    unsigned char month() const       { return m; }
    unsigned char day() const         { return d; }
    unsigned char hour() const        { return hh; }
    unsigned char minute() const      { return mm; }
    unsigned char second() const      { return ss; }

    unsigned char ram[DS1307_RAM_SIZE];
protected:
    unsigned char m, d, hh, mm, ss;
    unsigned short y;
};

extern TINYDS1307 tinyrtc;

#endif // _TINYDS1307_H_
