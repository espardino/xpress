#include <pin.h>
#include "gpiopin.h"
#include <mach.h>
#include "../../debug.h"

GPIOPin::GPIOPin(const char *name, uint32_t address, uint32_t mask, uint32_t access)
	:Pin(name,address,mask,access,NULL)
{
	printf("GPIOPin('%s',addr=%04x,mask=%04x,access=%d)\n",name,address,mask,access);
}

GPIOPin::~GPIOPin()
{
	
}

int32_t GPIOPin::getValue()
{
	uint16_t dat = FPGA_READ(address);
	DBG("GPIOPin::getValue() addr=%04x val=%04x\n",address,dat);
	return (dat&mask)?1:0;
}
void GPIOPin::setValue(int v)
{
	uint16_t res,dat;
	
	res = FPGA_WRITED(address)&(~mask);
	dat = res | (v?mask:0);	
	DBG("GPIOPin::setValue(%d) addr=%04x mask=%04x  %04x->%04x\n",v,address,mask,res,dat);
	FPGA_WRITE(address,dat);
}

void GPIOPin::setTris(int t)
{
	 uint16_t res,dat;
 
         res = FPGA_WRITED(address+1)&(~mask);
         dat = res | (t?mask:0);            
	DBG("GPIOPin::setTris(%d) addr=%04x mask=%04x\n",t,address,mask);
	FPGA_WRITE(address+1,dat);
}

int32_t GPIOPin::readADC()	{	return -1;	}
int32_t GPIOPin::getADCMax()	{	return -1;	}
