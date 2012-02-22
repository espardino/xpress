#!/bin/sh

SWIG_OPTS=-c++ -outcurrentdir -I.. \
	-I../../libraries/arduino/ -I../../libraries/core/ ../xpress.i

OBJS = xpress_wrap.o 
LIBS = ../../libraries/arduino/arduino_core.a ../../libraries/core/xpress_core.a
LIB = libXpress.so

all: $(LIB) test.exe
Xpress.cs xpress_wrap.cxx : ../xpress.i 
	swig -csharp -namespace Espardino $(SWIG_OPTS)

xpress_wrap.o : xpress_wrap.cxx
	$(CXX) -I.. -I../../libraries/arduino/ -I../../libraries/core -c xpress_wrap.cxx 

$(LIB): $(OBJS) 
	$(CXX) -shared $(OBJS) $(LIBS) -g -lrt -o $(LIB)

test.exe: test.cs Xpress.cs $(LIB) 
	mcs -out:test.exe *.cs


clean:
	rm -f $(OBJS) $(LIB) Xpress.cs test.exe SWIGTYPE_p_f_void__void.cs   
	rm -f XpressPINVOKE.cs xpress_wrap.cxx 

