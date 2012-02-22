#ifndef __PWM0Pin_h
#define __PWM0Pin_h

#include <pin.h>
#include <registers.h>

class PWM0Pin : public Pin
{
public:
	PWM0Pin(const char *name, uint32_t address, uint32_t mask, uint32_t access, Clock *clock);
	~PWM0Pin();  
	
	int32_t getValue();
	void setValue(int v);
	void setTris(int t);
	
	int32_t readADC();
	int32_t getADCMax();
};

#endif
