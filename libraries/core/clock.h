#ifndef __clock_h
#define __clock_h

#include <stdint.h>
#include <xml/tinyxml.h>



#define CLKDRIVER_FDIV  0x0001
#define CLKDRIVER_MAIN  0xffff

class ResourceMap;

class Clock
{
	uint32_t address,mask;
	uint32_t driver;
	uint32_t access;
	double speed;
	char *name;
	Clock *parent;
	ResourceMap *rmap;
	
public:
	
	Clock(ResourceMap *rmap);
	~Clock();
	
	
	int scanXML(TiXmlNode *xml);
	void setName(const char *name);
	const char *getName();
	void setParent(Clock *parent);
	
	void setAddress(uint32_t addr);
	void setMask(uint32_t mask);
	
	int setDriver(const char *driverName);
	double setSpeed(double speed);
	double getSpeed();

};

#endif
