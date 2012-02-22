#!/bin/sh

SWIG_OPTS=-c++ -outcurrentdir -I.. \
	-I../../libraries/arduino/ -I../../libraries/core/ ../xpress.i

OBJS = xpress_wrap.o 
LIBS = ../../libraries/arduino/arduino_core.a ../../libraries/core/xpress_core.a
LIB = _xpress.so

all: $(LIB) 
xpress.py xpress_wrap.cxx : ../xpress.i 
	swig -python $(SWIG_OPTS)

xpress_wrap.o : xpress_wrap.cxx
	$(CXX) -I/usr/include/python2.7 -I/usr/include/python2.4 -I.. -I../../libraries/arduino/ -I../../libraries/core -c xpress_wrap.cxx 

$(LIB): $(OBJS) 
	$(CXX) -shared $(OBJS) $(LIBS) -g -lrt -o $(LIB)


clean:
	rm -f $(OBJS) $(LIB) xpress.py xpress.pyc 
	rm -f xpress_wrap.cxx 

