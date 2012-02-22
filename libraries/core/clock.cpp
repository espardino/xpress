#include "clock.h"
#include "resourcemap.h"
#include "result.h"
#include <stdlib.h>
#include <string.h>
#include "../../debug.h"


 /**
  * Clock class. Handles a clock related to a parent clock
  * It allows the operations of changing and getting speed. Other peripheral
  * are related to this clock.
  */
Clock::Clock(ResourceMap *rm)
{
	parent=NULL;
	name = NULL;
	address = 0xffffffff;
	mask = 0xffffffff;
	rmap = rm;
	
}

Clock::~Clock()
{
	if (name) free(name);
}


int Clock::scanXML(TiXmlNode *xml)
{
	const char *name_str,*driver_str,*access_str, *clock_str;
	uint32_t addr, mask,access;
	int res;
	
	// get the strings for names, driver, access, clock.
	name_str 	= xml->ToElement()->Attribute("name");
	driver_str 	= xml->ToElement()->Attribute("driver");
	access_str 	= xml->ToElement()->Attribute("access");
	clock_str 	= xml->ToElement()->Attribute("clock");
	
	if (!name_str || !driver_str || !clock_str) return ERROR_XML;
	
	if (xml->ToElement()->QueryHexAttribute("addr",&addr)!=TIXML_SUCCESS)
	{
		fprintf(stderr,"addr field not found for clock \"%s\"\n",name_str);
		return ERROR_XML;
	}
	
	if (xml->ToElement()->QueryHexAttribute("mask",&mask)!=TIXML_SUCCESS)
	{
		fprintf(stderr,"mask field not found for clock \"%s\"\n",name_str);
		return ERROR_XML;
	}
	
	if (strcmp(access_str,"rw")==0)     access = RW_REG;
	else if (strcmp(access_str,"r")==0) access = R_REG;
	else if (strcmp(access_str,"w")==0) access = W_REG;
	else { access = RW_REG; }
	
	DBG("CLOCK: %4s %10s %s %04x %04x %d\n",name_str,driver_str,clock_str,addr,mask,access); 
	
	this->setName(name_str);
	this->parent = rmap->getClock(clock_str);
	if (!this->parent) {
		fprintf(stderr,"couldn't find parent clock \"%s\"\n",clock_str);
		return ERROR_XML;
	}
	this->access = access;
	
	res = this->setDriver(driver_str);
	if (res!=RES_OK) return res;
		
	this->setAddress(addr); 
	this->setMask(mask);
	
	return RES_OK;
}

 /**
  * Set the name of the clock.
  * @param name is the name we want to give to the clock.
  */
void Clock::setName(const char *name)
{
	if (this->name) free(this->name);
	this->name = strdup(name);
}

 /**
  * read the name of the clock.
  * @return the name of the clock.
  */
const char *Clock::getName()
{
	return name;
}

 /**
  * Set the parent of the clock. That clock gives the input signal to 
  * this clock module.
  * @param parent is the parent clock that inputs into this one.
  */
void Clock::setParent(Clock *parent)
{
	this->parent = parent;
}

 /**
  * set the register address of this clock.
  * @param addr is the address.
  */

void Clock::setAddress(uint32_t addr)
{
	this->address = addr;
}
 /**
  * set the mask of register for this clock. Those are the bits that
  * can be used in the clock register.
  * @return the name of the clock.
  */

void Clock::setMask(uint32_t mask)
{
	this->mask = mask;
}

 /**
  * set the driver that handles this clock set speed operation.
  * @return the status of the operation.
  */
int Clock::setDriver(const char *driverName)
{
	if (strcmp(driverName,"FDIV")==0)
	{
		this->driver = CLKDRIVER_FDIV;
	} else if (strcmp(driverName,"MAIN")==0)
	{
		this->driver = CLKDRIVER_MAIN;
	}
	else
	{
		return ERROR_UNKNOWN_DRIVER;
	}
	
	return RES_OK;
}

 /**
  * set the speed of the clock.
  * @param speed is the speed we want to set.
  * @return the real speed we were able to set.
  */
double Clock::setSpeed(double speed)
{
	this->speed = speed;
	return speed;
}

 /**
  * read the current speed of the clock.
  * @return speed of the clock output.
  */
double Clock::getSpeed()
{
	return this->speed;
}
