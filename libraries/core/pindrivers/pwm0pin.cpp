#include "pwm0pin.h"

PWM0Pin::PWM0Pin(const char *name, uint32_t address, uint32_t mask, uint32_t access, Clock *clock)
	:Pin(name,address,mask,access,clock)
{
	
	
	
	
	
}
PWM0Pin::~PWM0Pin()
{
}


int32_t PWM0Pin::getValue()
{
	return -1;
		
}
void PWM0Pin::setValue(int v)
{
}

void PWM0Pin::setTris(int t)
{
	
}

int32_t PWM0Pin::readADC()	{	return -1;	}
int32_t PWM0Pin::getADCMax()	{	return -1;	}

