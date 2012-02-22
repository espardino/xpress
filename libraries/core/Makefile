#CC=arm-none-linux-gnueabi-gcc
#CXX=arm-none-linux-gnueabi-g++

#CC=gcc
#CXX=g++
#AR=ar
#RANLIB=ranlib

CFLAGS=-g -c -Wall -I. -O0
CXXFLAGS=$(CFLAGS) -DDEBUG
LDFLAGS=-g -lm 

SOURCES_C=pins.c mach-lpc313x/lpc313x_hw.c mach-sim/generic_sim.c

SOURCES_CPP=xml/xmldump.cpp xml/tinystr.cpp  xml/tinyxml.cpp  xml/tinyxmlerror.cpp  xml/tinyxmlparser.cpp \
	    resourcemap.cpp clock.cpp pinfactory.cpp \
	    pin.cpp \
	    pindrivers/gpiopin.cpp pindrivers/pwm0pin.cpp pindrivers/lpcpin.cpp

TEST_CPP=test.cpp

OBJECTS_C=$(SOURCES_C:.c=.o)
OBJECTS_CPP=$(SOURCES_CPP:.cpp=.o)
OBJECTS_TEST_CPP=$(TEST_CPP:.cpp=.o)

OBJECTS=$(OBJECTS_C) $(OBJECTS_CPP) 
OBJECTS_TEST=$(OBJECTS) $(OBJECTS_TEST_CPP)

EXECUTABLE=test-core
LIBRARY=xpress_core.a

all: $(SOURCES_C) $(SOURCES_CPP) $(EXECUTABLE) $(LIBRARY)
	
clean:
	rm -f $(OBJECTS) $(OBJECTS_TEST_CPP)
	rm -f $(EXECUTABLE)
	rm -f $(LIBRARY)

$(EXECUTABLE): $(OBJECTS) $(OBJECTS_TEST)
	$(CXX) $(LDFLAGS) $(OBJECTS_TEST) -o $@

$(LIBRARY): $(OBJECTS)
	$(AR) rcs $(LIBRARY) $(OBJECTS)
#	$(RANLIB) $(LIBRARY)
.c.o:
	$(CC) $(CFLAGS) $< -o $@


.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

