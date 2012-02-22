#ifndef __mach_h
#define __mach_h

	#ifdef __i386
		#include "mach-sim/generic_sim.h"
	#else
		#include "mach-lpc313x/lpc313x_hw.h"
	#endif

#endif

