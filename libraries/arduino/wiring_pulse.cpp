/*
  wiring_pulse.c - pulseIn() function
  Part of Espardino Xpress - http://www.espardino.com/

  Copyright (c) 2005-2006 David A. Mellis
  Copyright (c) 2012	  Miguel Angel Ajo Pelayo

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

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/

#include "wiring_private.h"
#include <resourcemap.h>
#include <pin.h>
 	


/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{	
	unsigned long maxloops = timeout*100; /* TODO: tune */
	unsigned long numloops = 0;
	uint32_t m_start;
	
	ResourceMap *rmap = ResourceMap::getInstance();
	Pin *p = rmap->getPin(pin);
	
	if (!p) return 0;
	
	// wait for any previous pulse to end
	while (p->getValue() == state)
		if (numloops++ == maxloops)
			return 0;
	
	// wait for the pulse to start
	while (p->getValue()!=state)
		if (numloops++ == maxloops)
			return 0;
	
	// get start microsecond	
	m_start = micros();
	
	while (p->getValue()==state);

 	// return the difference 
	return (m_start - micros()); 
}
