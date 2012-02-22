
#include <WProgram.h>
#include <resourcemap.h>

int setupHardware(const char *name)
{
        ResourceMap *rmap = ResourceMap::getInstance();
        return rmap->loadCore(name);

}


