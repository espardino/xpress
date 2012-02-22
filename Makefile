DIRS = libraries/core libraries/arduino wrappers
LIBS = libraries/core/xpress_core.a \
	libraries/arduino/arduino_core.a

WRAPPERS = wrappers/cs_wrappers/libxpress.so



all: $(LIBS) $(WRAPPERS)

libraries/core/xpress_core.a : force_look
	echo looking into xpress
	cd libraries/core ; make $(MKFLAGS)


libraries/arduino/arduino_core.a : force_look
	echo looking into arduino
	cd libraries/arduino ; make

wrappers/cs_wrappers/libxpress.so : force_look
	echo looking into wrappers 
	cd wrappers; make

clean:
	echo cleaning up
	for d in $(DIRS); do (cd $$d; make clean ); done

force_look:
	true
	

