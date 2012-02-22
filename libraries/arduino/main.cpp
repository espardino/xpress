#include <WProgram.h>
#include <resourcemap.h>
#include <stdlib.h>

__attribute__((weak)) void setupXpress()
{
	fprintf(stderr,"Using default core0 Xpress FPGA Hardware\n");
        setupHardware("core0");
}

int main(void)
{
	init();
	
	setupXpress();
	
	setup();
    
	for (;;)
		loop();
        
	return 0;
}

