#include <pinfactory.h>
#include <resourcemap.h>
#include <pin.h>
#include <clock.h>
#include <pindrivers/lpcpin.h>
#include <pindrivers/gpiopin.h>
#include <pindrivers/pwm0pin.h>
#include <result.h>
#include "../../config.h"
#include "../../debug.h"

int PinFactory::getPinFromXML(TiXmlNode *xml, Pin** pin)
{
	ResourceMap *rmap = ResourceMap::getInstance();
	
	const char *name_str,*driver_str,*access_str, *clock_str;
	Clock *clock;
	uint32_t addr, mask,access;
	int res;
	
	// get the strings for names, driver, access, clock.
	name_str 	= xml->ToElement()->Attribute("name");
	driver_str 	= xml->ToElement()->Attribute("driver");
	access_str 	= xml->ToElement()->Attribute("access");
	clock_str 	= xml->ToElement()->Attribute("clock");
	res = rmap->getXMLAttribute(xml,"addr",&addr);
	res +=rmap->getXMLAttribute(xml,"mask",&mask);
	
	if (strcmp(access_str,"rw")==0)     access = RW_REG;
	else if (strcmp(access_str,"r")==0) access = R_REG;
	else if (strcmp(access_str,"w")==0) access = W_REG;
	else { access = RW_REG; }
	
	DBG("PIN: %4s %10s %s %04x %04x %d\n",name_str,driver_str,clock_str,addr,mask,access); 
	
	if (!name_str || !driver_str || (res<0)) return ERROR_XML;
	
	if (clock_str)
	{
		clock = rmap->getClock(clock_str);
		if (!clock)  DBG("Clock %s not found in resource map\n",clock_str);
	}
	else clock = NULL;
	
	*pin = getPinDriver(driver_str,name_str,addr,mask,access,clock);
	
	return pin ? RES_OK:ERROR_UNKNOWN_DRIVER;

}


Pin* PinFactory::getPinDriver(const char *driver_name,const char *name, uint32_t address, 
		  uint32_t mask, uint32_t access, Clock *clock)
{
	if (strcmp(driver_name,"NATIVE")==0)
	{
		return (Pin *) new LPCPin(name,address);
	} 
	else if (strcmp(driver_name,"GPIO")==0)
	{
		return (Pin *) new GPIOPin(name,address,mask,access);
	} 
	else if (strcmp(driver_name,"PWM0")==0)
	{
		return (Pin *)new PWM0Pin(name,address,mask,access,clock);
	} 
	else
	{
		DBG("Unknown driver '%s'\n",driver_name);
		return NULL;
	}
	
	
}
