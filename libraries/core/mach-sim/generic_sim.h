#ifndef __lpc31xx_hw_h
#define __lpc31xx_hw_h

#ifdef __cplusplus
extern "C" {
#endif
	
	void generic_sim_init();
	
	
	int sim_gpio_direction_input(unsigned gpio);
	int sim_gpio_get_value(unsigned gpio);
	void sim_gpio_set_value(unsigned gpio, int value);
	void sim_gpio_ip_function(int gpio);
	
	void sim_fpga_write(uint32_t addr, uint16_t value);
	uint16_t sim_fpga_read(uint32_t addr);
	uint16_t sim_fpga_writed(uint32_t addr);
#ifdef __cplusplus
}
#endif

#define MACH_INIT() generic_sim_init()
#define GPIO_DIR_INPUT(x) sim_gpio_direction_input(x)
#define GPIO_GET_VALUE(x) sim_gpio_get_value(x)
#define GPIO_SET_VALUE(x,y) sim_gpio_set_value(x,y)
#define GPIO_IP_FUNCTION(x) sim_gpio_ip_function(x)

#define FPGA_WRITE(addr,value) sim_fpga_write(addr,value)
#define FPGA_READ(addr)	       sim_fpga_read(addr)
#define FPGA_WRITED(addr)	       sim_fpga_writed(addr)

#endif
