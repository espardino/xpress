#ifndef __resourcemap_h
#define __resourcemap_h

#include "pins.h"
#include "clock.h"
#include <stdint.h>
#include <vector>
#include <list>

class TiXmlNode;

#define R_REG 0x01
#define W_REG 0x02
#define RW_REG  (R_REG|W_REG)

#define MAX_PINS 256

using namespace std;

class Pin;

class ResourceMap
{
public:
	ResourceMap();
	~ResourceMap();
	
	static ResourceMap* getInstance();
	
	Clock *getClock(const char *name);
	void *getSerial(int n);
	void *getSerial(uint8_t rx, uint8_t tx);
	Pin *getPin(uint8_t gpio);
	void *getSPIDriver(uint8_t cs, uint8_t miso, uint8_t mosi, uint8_t sck);
	
	int getPinNumber(const char *name);
	uint8_t getPinID(const char *name);
	const char* getPinName(uint8_t id);
	
	int loadCore(const char *name);
	
	int getXMLAttribute(TiXmlNode *xml, const char* name,unsigned int *attr);
	
private:
	static ResourceMap *instance;
	
	
	Pin* pins[MAX_PINS];
	list<Clock *> clocks;
	
	unsigned int core_id;
	unsigned int core_addr;
	char *core_description;
	
	
	void createNativeDrivers();
	
	
	int scanCoreXMLClock(TiXmlNode *xml);
	int scanCoreXMLPin(TiXmlNode *xml);
	int scanCoreXMLClocks(TiXmlNode *xml);
	int scanCoreXMLPins(TiXmlNode *xml);
	int scanCoreXML(TiXmlNode *xml);
	int scanXML(TiXmlNode *xml);
	
};


#endif
