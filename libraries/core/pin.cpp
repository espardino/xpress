#include "pin.h"
#include "../../debug.h"

Pin::Pin(const char *name, uint32_t address, uint32_t mask, 
	    uint32_t access, Clock *clock)
{
	this->name = NULL;
	this->driver_name = NULL;
	
	this->setName(name);       
	this->setAddress(address); 
	this->setMask(mask);       
	this->setAccess(access);   
	this->setClock(clock);     
}

Pin::~Pin()
{
	if (name) free(name);
	if (driver_name) free(driver_name);
}

void Pin::setName(const char *name)
{
	if (this->name) free(this->name);
	this->name = strdup(name);
	
}
const char * Pin::getName()
{
	return this->name;	
}

void Pin::setClock(Clock *parent)
{
	this->clock = parent;	
}

void Pin::setAddress(uint32_t addr)
{
	//DBG("setAddress(%04x)\n",addr);
	this->address = addr;	
}

void Pin::setAccess(uint32_t access)
{
	this->access = access;	
}

void Pin::setMask(uint32_t mask)
{
	//DBG("setMask(%04x)\n",mask);
	this->mask = mask;
}	

int32_t Pin::getValue()
{
	return -1;
		
}
void Pin::setValue(int v)
{
}

void Pin::setTris(int t)
{
	
}

int32_t Pin::readADC()	{	return -1;	}
int32_t Pin::getADCMax()	{	return -1;	}






void Pin::setDriverName(const char *driver_name)
{
	if (this->driver_name) free (this->driver_name);
	this->driver_name = strdup(driver_name);	
}

const char* Pin::getDriverName()
{
	return driver_name;
}
	
