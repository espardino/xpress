#ifndef __Pin_h
#define __Pin_h

#include <stdint.h>
#include <xml/tinyxml.h>

#define TRIS_INPUT 	0x0000
#define TRIS_OUTPUT 	0x0001


class ResourceMap;
class Clock;

class Pin
{
protected:
	uint32_t address,mask;
	uint32_t access;
	int last_val;
	char *name;
	char *driver_name;
	Clock *clock;
	ResourceMap *rmap;
	
public:
	
	Pin(const char *name, uint32_t address, uint32_t mask, 
	    uint32_t access, Clock *clock=NULL);
	
	virtual ~Pin();
	
	void setName(const char *name);
	const char *getName();
	void setClock(Clock *parent);
	
	void setAddress(uint32_t addr);
	void setAccess(uint32_t access);
	void setMask(uint32_t mask);
	
	void setDriverName(const char *driverName);
	const char* getDriverName();
	
	virtual int32_t getValue();
	virtual void setValue(int v);
	virtual void setTris(int t);
	
	virtual int32_t readADC();
	virtual int32_t getADCMax();
	
	

};

#endif
