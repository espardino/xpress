/*
  wiring_export.h - Partial implementation of the Wiring API for Espardino.
  Part of Espardino http://www.espardino.com

  Copyright (c) 2012 Miguel Angel Ajo Pelayo

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id$
*/

#ifndef Wiring_Exports_h
#define Wiring_Exports_h

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

const uint8_t HIGH=0x1;
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define HWFUNCTION 0x2

#define true 0x1
#define false 0x0

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3
#define INTERNAL 3
#define DEFAULT 1
#define EXTERNAL 0


void init(void);

int setupHardware(const char *name);

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);

int analogRead(uint8_t);
void analogReference(uint8_t mode);
void analogWrite(uint8_t, int);

uint32_t millis(void);
uint32_t micros(void);
void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);
unsigned long pulseIn(uint8_t pin_n, uint8_t state, unsigned long timeout);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

/*
void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);
*/

#ifdef __cplusplus
} // extern "C"
#endif

#endif
