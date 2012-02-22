DIRS = cs_wrappers 
LIBS=cs_wrappers/libxpress.so

all: $(LIBS) $(WRAPPERS)

cs_wrappers/libxpress.so Xpress.cs : force_look
	echo Building C# wrappers	
	cd cs_wrappers ; make


clean:
	echo cleaning up
	for d in $(DIRS); do (cd $$d; make clean ); done

force_look:
	true
	

