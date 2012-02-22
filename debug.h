#ifndef __debug_h
#define __debug_h
#include <stdio.h>

#ifdef DEBUG
	#define DBG(fmt, args...)    fprintf(stdout, fmt, ## args)
#else
	#define DBG(fmt, args...)    /* Don't do anything in release builds */
#endif

#endif
