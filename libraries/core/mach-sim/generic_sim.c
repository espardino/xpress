#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "../mach-lpc313x/lpc313x_gpio.h"

int generic_sim_init()
{
	printf("generic_sim_init()\n");
	return 0;
}

inline uint32_t sim_fpga_translate_addr(uint32_t addr)
{
// Translate address from:   0000000000abcdef
//                     to:   ab0000000000cdef
// because only A15,A14,A3,A2,A1,A0 is connected from LPC31xx to FPGA
	uint32_t extb_addr = (addr&0x000F) + 
			     ((addr&0x0030)<<10); 
	return extb_addr;
}
uint16_t fpga_write_data[63];

void sim_fpga_write(uint32_t addr, uint16_t value)
{              
	fpga_write_data[addr]=value;	
	printf("fpga[%02x]<=%04x\n",addr,value);
}
uint16_t sim_fpga_writed(uint32_t addr)
{
	return fpga_write_data[addr];
}


uint16_t sim_fpga_read(uint32_t addr)
{
	printf("fpga[%02x]=>\n",addr);
	return 0xE000;
}



int sim_gpio_direction_input(unsigned gpio)
{

	printf("gpio %08x as input\n",gpio);

	return 0;
}


int sim_gpio_get_value(unsigned gpio)
{
	printf("READ gpio %08x\n",gpio);
	return 1;
}

void sim_gpio_set_value(unsigned gpio, int value)
{
	printf("WRITE gpio %08x as '%d'\n",gpio,value?1:0);
	
}

void sim_gpio_ip_function(int gpio)
{
	printf("SET IP on gpio %08x\n",gpio);
}

