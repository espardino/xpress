/*
  wiring.c - Partial implementation of the Wiring API for the Xpress platform
  Part of Espardino Xpress - http://www.espardino.com/

  Copyright (c) 2005-2006 David A. Mellis
  Copyright (c) 2012 Miguel Angel Ajo

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

#include "wiring_private.h"
#include <time.h>
#include <unistd.h>
#include <mach.h>
#include <stdint.h>

uint64_t millis_zero=0;

uint32_t millis()
{
	uint64_t t;
        struct timespec ts;
        if(clock_gettime(CLOCK_MONOTONIC,&ts) != 0) {           
                fprintf(stderr,"couldn't clock_gettime()\n");
                return -1;
        }
        
        t = ts.tv_sec*1000;
        t+= ts.tv_nsec/1000000;
        t-=millis_zero;
        
        return  (uint32_t) t;
        
}

uint64_t micros_zero = 0;
uint32_t micros() {
	uint64_t t;
        struct timespec ts;
        if(clock_gettime(CLOCK_MONOTONIC,&ts) != 0) {           
                fprintf(stderr,"couldn't clock_gettime()\n");
                return -1;
        }
        
        t = ts.tv_sec*1000000;
        t+= ts.tv_nsec/1000;
        t-= micros_zero;
        
        return  (uint32_t) t;
}

void delay(uint32_t ms)
{
	usleep(ms*1000);
}


void delayMicroseconds(uint32_t us)
{
	usleep(us);
}

void init()
{

	millis_zero = millis();
	micros_zero = micros();
	MACH_INIT(); // initialize our machine
	
}
