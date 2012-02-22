#ifndef __LPCPin_h
#define __LPCPin_h


#include <pin.h>

class LPCPin : public Pin
{
public:
	LPCPin(const char *name, uint32_t address);
	~LPCPin();
	
	int32_t getValue();
	void setValue(int v);
	void setTris(int t);
	
	int32_t readADC();
	int32_t getADCMax();
};

#endif
