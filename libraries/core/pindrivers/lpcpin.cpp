#include <pin.h>
#include "lpcpin.h"
#include <mach.h>

LPCPin::LPCPin(const char *name, uint32_t id)
	:Pin(name,id,0,0,NULL)
{
	
}

LPCPin::~LPCPin()
{
	
}

int32_t LPCPin::getValue()
{
	return GPIO_GET_VALUE(address); 
}
void LPCPin::setValue(int v)
{
	GPIO_SET_VALUE(address,v);
	last_val = v;
}

void LPCPin::setTris(int t)
{
	switch(t)
	{
	 case 1:	GPIO_SET_VALUE(address,last_val); break;
	 case 0:	GPIO_DIR_INPUT(address);    break;
	 case 2:        GPIO_IP_FUNCTION(address);        break;
	 default:       GPIO_SET_VALUE(address,last_val); break;
	}
}

int32_t LPCPin::readADC()	{	return -1;	}
int32_t LPCPin::getADCMax()	{	return -1;	}
