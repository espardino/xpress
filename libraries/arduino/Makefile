
CFLAGS=-g -c -Wall -I. -I../core -I../core/pindrivers -O0
CXXFLAGS=$(CFLAGS) -DDEBUG
LDFLAGS=-g -lm 

SOURCES_C=wiring.c wiring_shift.c
SOURCES_CPP=xpress.cpp wiring_analog.cpp wiring_digital.cpp wiring_pulse.cpp Print.cpp WMath.cpp WString.cpp

TEST_CPP=test.cpp main.cpp

OBJECTS_C=$(SOURCES_C:.c=.o)
OBJECTS_CPP=$(SOURCES_CPP:.cpp=.o)
OBJECTS_TEST_CPP=$(TEST_CPP:.cpp=.o)

OBJECTS=$(OBJECTS_C) $(OBJECTS_CPP) 
OBJECTS_TEST=$(OBJECTS_TEST_CPP)

EXECUTABLE=test-arduino
LIBRARY=arduino_core.a

all: $(SOURCES_C) $(SOURCES_CPP) $(EXECUTABLE) $(LIBRARY)
	
clean:
	rm -f $(OBJECTS) $(OBJECTS_TEST)
	rm -f $(EXECUTABLE)
	rm -f $(LIBRARY)

$(EXECUTABLE): $(OBJECTS) $(OBJECTS_TEST) $(LIBRARY)
	$(CXX) $(LDFLAGS) $(OBJECTS_TEST) $(LIBRARY) ../core/xpress_core.a -o $@ -lrt

$(LIBRARY): $(OBJECTS)
	$(AR) rcs $(LIBRARY) $(OBJECTS)
#	$(RANLIB) $(LIBRARY)
.c.o:
	$(CC) $(CFLAGS) $< -o $@


.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

