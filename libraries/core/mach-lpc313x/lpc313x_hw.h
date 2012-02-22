#ifndef __lpc31xx_hw_h
#define __lpc31xx_hw_h

#ifdef __cplusplus
extern "C" {
#endif

	extern uint16_t *LPC31XX_SRAM;
	extern uint32_t *LPC31XX_MPMC;
	extern uint32_t *LPC31XX_CGU;
	
	void lpc31xx_init();
	
	
	int lpc31xx_gpio_direction_input(unsigned gpio);
	int lpc31xx_gpio_get_value(unsigned gpio);
	void lpc31xx_gpio_set_value(unsigned gpio, int value);
	void lpx31xx_gpio_ip_function(int gpio);
	
	void fpga_write(uint32_t addr, uint16_t value);
	uint16_t fpga_writed(uint32_t addr);
	uint16_t fpga_read(uint32_t addr);
#ifdef __cplusplus 
}
#endif

#define MACH_INIT() lpc31xx_init()
#define GPIO_DIR_INPUT(x) lpc31xx_gpio_direction_input(x)
#define GPIO_GET_VALUE(x) lpc31xx_gpio_get_value(x)
#define GPIO_SET_VALUE(x,y) lpc31xx_gpio_set_value(x,y)
#define GPIO_IP_FUNCTION(x) lpx31xx_gpio_ip_function(x)

#define FPGA_WRITE(addr,value) fpga_write(addr,value)
#define FPGA_WRITED(addr)      fpga_writed(addr)
#define FPGA_READ(addr)	       fpga_read(addr)

#endif
