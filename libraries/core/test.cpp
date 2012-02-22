
#include <stdlib.h>
#include <stdio.h>
#include "resourcemap.h"
#include <mach.h>
#include "pin.h"
#include <assert.h>



int main(int argc, char **argv)
{
	MACH_INIT(); // initialize our machine
	ResourceMap *rmap = ResourceMap::getInstance();
	rmap->loadCore("core0");
	
	Pin *p = rmap->getPin(F27);
	assert(p!=NULL);
	p->setValue(1);
	p->setTris(1);
	
	Pin *p1 = rmap->getPin(F75);
	assert(p1!=NULL);
	
	p1->setValue(1);
	p1->setTris(1);
	
	
	Pin *p2 = rmap->getPin(G14);
	assert(p2!=NULL);
	p2->setValue(0);
	p2->setTris(0);
	
}
