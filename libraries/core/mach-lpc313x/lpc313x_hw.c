#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "lpc313x_gpio.h"
#include "../../../debug.h" 
#define SRAM_BASE  0x20000000
#define SRAM_LENGTH   0x0040000

#define MPMC_BASE  0x17008000
#define MPMC_LENGTH 0x10000

#define CGU_BASE     0x13004000
#define CGU_LENGTH   0x00010000

static void *IOCONF_MAPPED_ADDR;
uint16_t *LPC31XX_SRAM;
uint32_t *LPC31XX_MPMC;
uint32_t *LPC31XX_CGU;

int  lpc31xx_dev_mem_fd;

int lpc31xx_mmap_init()
{
	lpc31xx_dev_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
        if (lpc31xx_dev_mem_fd < 0) {
                perror("open /dev/mem");
                return -1;
        }

        LPC31XX_SRAM = mmap(NULL, SRAM_LENGTH, PROT_READ | PROT_WRITE,
				MAP_SHARED, lpc31xx_dev_mem_fd, SRAM_BASE);
				
        if (LPC31XX_SRAM == MAP_FAILED) {
                perror("mmap EXTSRAM");
                close(lpc31xx_dev_mem_fd);
                return -2;
        }

        LPC31XX_MPMC = mmap(NULL, MPMC_LENGTH,PROT_READ | PROT_WRITE,
				MAP_SHARED, lpc31xx_dev_mem_fd, MPMC_BASE);

        if (LPC31XX_MPMC == MAP_FAILED) {
                perror("mmap MPMC");
                close(lpc31xx_dev_mem_fd);
                return -2;
        }

        LPC31XX_CGU = mmap(NULL, CGU_LENGTH,PROT_READ | PROT_WRITE,
				MAP_SHARED, lpc31xx_dev_mem_fd, CGU_BASE);

        if (LPC31XX_CGU == MAP_FAILED) {
                perror("mmap CGU");
                close(lpc31xx_dev_mem_fd);
                return -2;
        }


	IOCONF_MAPPED_ADDR = mmap(NULL, IOCONF_LENGTH, PROT_READ | PROT_WRITE,
					MAP_SHARED, lpc31xx_dev_mem_fd, IOCONF_BASE);
	
	if (IOCONF_MAPPED_ADDR == MAP_FAILED) {
		perror("mmap IOCONF_BASE");
		close(lpc31xx_dev_mem_fd);
		return -2;
	}
	return 0;



        return 0;
}

void lpc31xx_ext_sram_init()
{
	LPC31XX_MPMC[0x200/4]=0x81; // 16bit, ignore lanes 
	LPC31XX_MPMC[0x204/4]=0x01; // chipselect + address setup to WE delay
	LPC31XX_MPMC[0x208/4]=0x01; // chipselect + address setup to OE delay
	LPC31XX_MPMC[0x20c/4]=0x02; // chipselect to read access delay
	LPC31XX_MPMC[0x210/4]=0x02; // chipselect to read on page mode delay
	LPC31XX_MPMC[0x214/4]=0x02; // chipselect to write
	LPC31XX_MPMC[0x218/4]=0x0f; // turnarraound cycles when SDRAM <-> EXTSRAM change on bus
}

void lpc31xx_cgu_init()
{
 	LPC31XX_CGU[0xFC/4]|=0x11; // PCR15: enable & run CLOCK_OUT (15)
        LPC31XX_CGU[(0x3A0/4)+15]=(5<<1)|1; //use  FD5 | enabled
        LPC31XX_CGU[(0x578/4)+5]=LPC31XX_CGU[(0x578/4)+15]&(~2); // disable ALLOW for DYN_FD5
        LPC31XX_CGU[(0x518/4)+5]=(0xff<<11)|(3<<3)|(1<<2)|(1<<0);
        
       /*v =CGU[(0x518/4)+5];
         printf("fd5 => msub=%d madd=%d st=%d rs=%d run=%d\n",(v>>11)&0xff, (v>>3)&0xff, v&4,v&2,v&1);
	
	
	// this is to see what fractional divider are using clocks 0 to 29 
	for (i=0;i<=29;i++)
	{
	        v=CGU[(0x3A0/4) + i];
	        if (v&1) v=v>>1;
	        else     v=0xffff;
	        printf("%d -> fd %d\n",i,v);
	}
	*/
	
}

int lpc31xx_init()
{
	DBG("lpc31xx_init()\n");
	if (lpc31xx_mmap_init()!=0) return -1;
	DBG("lpc31xx_init(): mmap ok\n");
	lpc31xx_ext_sram_init();
	lpc31xx_cgu_init();
	return 0;
}

inline uint32_t fpga_translate_addr(uint32_t addr)
{
// Translate address from:   0000000000abcdef
//                     to:   ab0000000000cdef
// because only A15,A14,A3,A2,A1,A0 is connected from LPC31xx to FPGA
	uint32_t extb_addr = (addr&0x000F) + 
			     ((addr&0x0030)<<10); 
	return extb_addr;
}


uint16_t writed_regs[64];
void fpga_write(uint32_t addr, uint16_t value)
{              
	LPC31XX_SRAM[fpga_translate_addr(addr)]=value;
	writed_regs[addr&63]=value;
}

uint16_t fpga_writed(uint32_t addr)
{
	return writed_regs[addr&63];
}

uint16_t fpga_read(uint32_t addr)
{
	return LPC31XX_SRAM[fpga_translate_addr(addr)];
}



int lpc31xx_gpio_direction_input(unsigned gpio)
{

	int port = (gpio & GPIO_PORT_MASK);
	int pin = 1 << (gpio & GPIO_PIN_MASK);

	GPIO_M1_RESET(port) = pin; 
	GPIO_M0_RESET(port) = pin;


	return 0;
}


int lpc31xx_gpio_get_value(unsigned gpio)
{
	return (GPIO_STATE(gpio & GPIO_PORT_MASK) & (1 << (gpio & GPIO_PIN_MASK)));
}

void lpc31xx_gpio_set_value(unsigned gpio, int value)
{
	int port = (gpio & GPIO_PORT_MASK);
	int pin = 1 << (gpio & GPIO_PIN_MASK);



	GPIO_M1_SET(port) = pin; 

	if(value) 	GPIO_M0_SET(port) = pin;
	else	  		GPIO_M0_RESET(port) = pin;
	
}

void lpx31xx_gpio_ip_function(int gpio)
{
	
	int port = (gpio & GPIO_PORT_MASK);
	int pin = 1 << (gpio & GPIO_PIN_MASK);

	GPIO_M1_RESET(port) = pin; 
	GPIO_M0_SET(port) = pin;

}

