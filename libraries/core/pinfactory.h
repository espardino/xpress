#ifndef __PinFactory_h
#define __PinFactory_h

#include <stdint.h>
#include <xml/tinyxml.h>


class ResourceMap;
class Pin;
class Clock;

class PinFactory
{

	
public:
	PinFactory(ResourceMap *rm);	
static	int getPinFromXML(TiXmlNode *xml,Pin** pin);
static Pin* getPinDriver(const char *driver_name,const char *name, uint32_t address, 
		  uint32_t mask, uint32_t access, Clock *clock);

	

};

#endif
