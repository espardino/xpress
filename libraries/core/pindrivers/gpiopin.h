#ifndef __GPIOPin_h
#define __GPIOPin_h


#include <pin.h>

class GPIOPin : public Pin
{
public:
	GPIOPin(const char *name, uint32_t address, uint32_t mask, uint32_t access);
	~GPIOPin();
	
	int32_t getValue();
	void setValue(int v);
	void setTris(int t);
	
	int32_t readADC();
	int32_t getADCMax();
};

#endif
