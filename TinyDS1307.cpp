// Scriptname : TinyDS1307.cpp
// Author     : Evgeniy Kiselyov
// Contact    : jeka911@gmail.com
// Date       : 2014-27-03
// Version    : 0.00001
// License    : The MIT License
// 
// Description:
// Library for ATtiny85 on Arduino for DS1307. With RAM support.
// Please check README.md file

#include "TinyDS1307.h"

static unsigned char bcd2bin (unsigned char val) { return val - 6 * (val >> 4); }
static unsigned char bin2bcd (unsigned char val) { return val + 6 * (val / 10); }

bool TINYDS1307::begin(void) {
  return true;
}

bool TINYDS1307::isrunning(void) {
  TinyWireM.beginTransmission(DS1307_ADDRESS);
  TinyWireM.send(0);
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(DS1307_ADDRESS, 1);
  uint8_t ss = TinyWireM.receive();
  return !(ss>>7);
}

bool TINYDS1307::adjust(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec) 
{
    if (year >= 2000)
        year -= 2000;
    TinyWireM.beginTransmission(DS1307_ADDRESS);
    TinyWireM.send(0);
    TinyWireM.send(bin2bcd(sec) | 0x80); // stop the clock
    TinyWireM.send(bin2bcd(min));
    TinyWireM.send(bin2bcd(hour));
    TinyWireM.send(bin2bcd(0));
    TinyWireM.send(bin2bcd(day));
    TinyWireM.send(bin2bcd(month));
    TinyWireM.send(bin2bcd(year));
    TinyWireM.send(0);
    
    if (TinyWireM.endTransmission() != 0)
	return false;

    TinyWireM.beginTransmission(DS1307_ADDRESS);
    TinyWireM.send(0);
    TinyWireM.send(bin2bcd(sec) & 0x7F); // start the clock

    if (TinyWireM.endTransmission() != 0)
	return false;

    return true;
}

bool TINYDS1307::read()  {
  TinyWireM.beginTransmission(DS1307_ADDRESS);
  TinyWireM.send(0);	
  if (TinyWireM.endTransmission() != 0)
	return false;

  TinyWireM.requestFrom(DS1307_ADDRESS, 7);
  ss = bcd2bin(TinyWireM.receive() & 0x7F);
  mm = bcd2bin(TinyWireM.receive());
  hh = bcd2bin(TinyWireM.receive() & 0x3f);
  TinyWireM.receive();
  d = bcd2bin(TinyWireM.receive());
  m = bcd2bin(TinyWireM.receive());
  y = bcd2bin(TinyWireM.receive()) + 2000;

  if (ss & 0x80) return false; // clock is halted
  return true;
}

bool TINYDS1307::read_ram(void) {
  TinyWireM.beginTransmission(DS1307_ADDRESS);
  TinyWireM.send(8);	 // RAM starts there
  if (TinyWireM.endTransmission() != 0)
	return false;
  TinyWireM.requestFrom(DS1307_ADDRESS, DS1307_RAM_SIZE);
  int tries = 0;
  while(!TinyWireM.available())
  {
    delay(50);
    tries++;
    if (tries == 20)   /// wait results for 1 sec max
	return false;
  }
  for(int i=0; i<DS1307_RAM_SIZE; i++)
  {
    ram[i] = TinyWireM.receive();
  }

  return true;
}

bool TINYDS1307::write_ram(void) {
  TinyWireM.beginTransmission(DS1307_ADDRESS);
  TinyWireM.send(8);	 // RAM starts there
  for(int i=0; i<DS1307_RAM_SIZE; i++)
  {
    TinyWireM.send(ram[i]);
  }	
  if (TinyWireM.endTransmission() != 0)
	return false;
  return true;
}

class TINYDS1307 tinyrtc;
