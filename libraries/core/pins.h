#ifndef __PINS_H
#define __PINS_H

#include <stdint.h>

#include "pin_constants.h"

#define PIN_TYPE_MASK 0xffff0000

typedef enum {
	ANALOG      =	  0x000A0000,
	FPGA	    = 	  0x000F0000,
	HWFUNCTION  =	  0x000E0000,
	NATIVEGPIO  =	  0x00100000
} pin_type; 


struct pin_entry {
	int	pin_number;
	uint8_t	id;
	pin_type  type;
	int native_id;
	const char* name;
	const char* info;
	// more to be defined here 
} ;

		


/*
Pin number Pin name Description Function group
1	 5V	 Supply pin	 POWER
2	 GND	 Ground	 POWER
17	 GND	 		Ground	 POWER
18	 GND	 		Ground POWER
28	 GND	 		Ground	 POWER

29	 nRSTO	 	Reset output (active low)	 POWER
30	 nRSTI	 	Reset input (active low) POWER

39	 GND	 		Ground	 POWER
40	 GND	 		Ground	 POWER
41	 VOUT_L	 	Audio output left AUDIO
42	 VIN_L	 	Audio input left AUDIO
43	 VOUT_R	 	Audio output right AUDIO
44	 VIN_R	 	Audio input right AUDIO
45	 HP_L	 		Audio headphones left AUDIO
46	 MIC	 		Audio mic input AUDIO
47	 HP_R	 		Audio headphones right AUDIO
48	 HP_GND	 	Audio headphones ground AUDIO
49	 D-	 			USB D- connection	 NB31XX
50	 D+	 			USB D+ connection	 NB31XX

95	 GND	 		Ground	 POWER
96	 3V3	 		Supply pin	 POWER


*/

extern const struct pin_entry pin_table[];

#endif
