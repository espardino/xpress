#include <xml/tinyxml.h>
#include <stdlib.h>
#include <stdio.h>
#include <result.h>
#include <resourcemap.h>
#include <pin.h>
#include <pinfactory.h>
#include "../../config.h"
#include "../../debug.h"


ResourceMap* ResourceMap::instance = NULL;
	
ResourceMap* ResourceMap::getInstance()
{
	if (instance==NULL)
	{
		instance = new ResourceMap();
	}
	return instance;
}

 /**
  * ResourceMap constructor. Initializes the class attributes.
  */

ResourceMap::ResourceMap()
{
	core_description = NULL;
	core_addr = 0xffffffff;
	core_id   = 0xffffffff;
	
	for (int i=0;i<MAX_PINS;i++)
		pins[i]=NULL;
		
	createNativeDrivers();
}

/**
 * creates objects for the native GPIOS, I2C, UART, etc.. 
 */
void ResourceMap::createNativeDrivers()
{
	const struct pin_entry* p=pin_table;
	while (p->pin_number>=0)
	{
		if (p->native_id>=0)
		{
			// DBG("creating native pin %s (%d)\n",p->name,p->id);
			Pin* pin_n= PinFactory::getPinDriver("NATIVE",p->name, p->native_id,0,0,NULL);
			pins[p->id]=pin_n;
		}
		p++;
	}
}

/**
  * ResourceMap destructor.
  */

ResourceMap::~ResourceMap()
{
	if (core_description) free(core_description);
}		

 /**
  * read an unsigned int attribute (hex) attribute from xml.
  * And stores it via attr pointer.
  * @param xml is the xml node where we want to take the attribute from.
  * @param name is the name of the attribute we want to get
  * @return RES_OK or ERROR_XML if the attribute was not found.
  */
int ResourceMap::getXMLAttribute(TiXmlNode *xml, const char* name,unsigned int *attr)
{
	
	if (xml->ToElement()->QueryHexAttribute(name,attr)!=TIXML_SUCCESS)
	{
		fprintf(stderr,
			"Error seeking for attribute %s in %s",name,xml->Value());
		return ERROR_XML;
	}
	return RES_OK;
}


/**
  * Scan a pin mapping information from core into the ResourceMap.
  * @param xml is the xml node "pin"
  * @return RES_OK or ERROR_XML if the attribute was not found.
  */
int ResourceMap::scanCoreXMLPin(TiXmlNode *xml)
{
	Pin *n_pin;
	int8_t id;
	// build a pin driver object from xml description
	int res = PinFactory::getPinFromXML(xml,&n_pin);
	
	// get the pin ID from table
	id = getPinID(n_pin->getName());
	//DBG("id for pin %s is %d\n",n_pin->getName(),id);
	// add it to our table
	if (id>=0)  pins[id]=n_pin;
	return res;
}

/**
  * Scan the pin mapping information from core into the ResourceMap.
  * @param xml is the xml node "pins"
  * @return RES_OK or ERROR_XML if the attribute was not found.
  */
int ResourceMap::scanCoreXMLPins(TiXmlNode *xml)
{
	//DBG("found pins\n");	
	
	TiXmlNode *cChild=xml->FirstChild();
	while(cChild!=0)
	{
		
		if (strcmp(cChild->Value(),"pin")==0)
		{
			scanCoreXMLPin(cChild);	
		}		
		cChild = cChild->NextSibling();
	}

	
	return RES_OK;
}


/**
  * Scan a clock mapping information from core into the ResourceMap.
  * @param xml is the xml node "clock"
  * @return RES_OK or ERROR_XML if the attribute was not found.
  */
int ResourceMap::scanCoreXMLClock(TiXmlNode *xml)
{
	int res;
	Clock *clock = new Clock(this);
	
	res = clock->scanXML(xml);
	
	if (res!=RES_OK)
	{
		delete clock;
		return res;
	}
	
	clocks.push_back(clock);
	
	return RES_OK;
}

/**
  * Get clock from resource map.
  * @param name is the name of the clock we want to get
  * @return pointer to clock.
  */
Clock *ResourceMap::getClock(const char *name)
{
	for(std::list<Clock *>::iterator list_iter = clocks.begin(); 
		list_iter != clocks.end(); list_iter++)
	{
	    //DBG("Is clock '%s' == '%s'?\n",(*list_iter)->getName(),name);
	    const char *i_name = (*list_iter)->getName();
	    if (strcmp(i_name,name)==0) return *list_iter;
	}
	
	return (Clock *)NULL;
}

/**
  * Scan the clock mapping information from core into the ResourceMap.
  * @param xml is the xml node "clocks"
  * @return RES_OK or ERROR_XML if the attribute was not found.
  */
int ResourceMap::scanCoreXMLClocks(TiXmlNode *xml)
{
	//DBG("found clocks\n");
	
	
	TiXmlNode *cChild=xml->FirstChild();
	while(cChild!=0)
	{
		
		if (strcmp(cChild->Value(),"clock")==0)
		{
			scanCoreXMLClock(cChild);	
		}		
		cChild = cChild->NextSibling();
	}
	
	return RES_OK;
}


/**
  * Scan the core node that will have the pins and clock nodes.
  * Also will read the core ID and the core id address.
  * @param xml is the xml node "pins"
  * @return RES_OK or ERROR_XML if the attribute was not found.
  */
int ResourceMap::scanCoreXML(TiXmlNode *xml)
{
	const char* description;
	TiXmlNode* cChild;             
	
	// Get the address and ID information from core node
	if ((getXMLAttribute(xml, "addr",&this->core_addr)<0)||
	    (getXMLAttribute(xml, "id",&this->core_id)<0))
	{
		return ERROR_XML;
	}
	
	// Get the core description and store it
	description = xml->ToElement()->Attribute("description");
	
	if (description) {
		if (core_description) free(core_description);
		core_description = strdup(description);
	} else {
		if (core_description) free(core_description);
		core_description = NULL;
	}
	
	cChild=xml->FirstChild();
	while(cChild!=0)
	{
		
		if (strcmp(cChild->Value(),"clocks")==0)
		{
			scanCoreXMLClocks(cChild);
			
		} else if (strcmp(cChild->Value(),"pins")==0)
		{
			scanCoreXMLPins(cChild);
		}
		
		cChild = cChild->NextSibling();
	}

	
	return 0;
}


/**
  * Scan the XML file that defines the core.
  * @param xml is the root of the XML document, must be a TINYXML_DOCUMENT
  * @return RES_OK or ERROR_XML if the attribute was not found.
  */
int ResourceMap::scanXML(TiXmlNode *xml)
{
	TiXmlNode* pChild;
	
	if (xml->Type()!=TiXmlNode::TINYXML_DOCUMENT)	
		return ERROR_XML;
	
	pChild = xml->FirstChild();
	
	while(pChild != 0) 
	{             
		if (strcmp(pChild->Value(),"core")==0)
		{
			return scanCoreXML(pChild);
		}
		pChild = pChild->NextSibling();
	}
	return ERROR_XML;
}

/**
  * Load a core information from XML and also program the FPGA where needed.
  * @param name is the name of the core, "core0" "core1" "coreSERVO" etc.
  * @return RES_OK or ERROR_XML if the attribute was not found.
  */
int ResourceMap::loadCore(const char *name)
{
	// Allocate memory to build the xml file path based on core name
	char *xml_path = (char *)malloc(strlen(name)*2+strlen(XPRESS_CORES)+8);
	
	// If we had no memory exit with error
	if (!xml_path) return ERROR_MEMORY; 
		
	// Build the file path
	sprintf(xml_path,XPRESS_CORES"%s/%s.xml",name,name);
	
	// Get a TinyXML document from the path
	TiXmlDocument core_definition(xml_path);
	
	// Read it, if everything was right, then scan the file
	bool ok = core_definition.LoadFile();
	
	if(ok)	
	{
		// Clear the pin and clock list
		this->clocks.clear();
		
		// Add the main clock to the list
		Clock *mainClock = new Clock(this);
	
		mainClock->setName("MAIN");
		mainClock->setDriver("MAIN");
		mainClock->setSpeed(45000000);
	
		clocks.push_back(mainClock);
	
		
		return scanXML(&core_definition);
	}
	else
	{
		// If there was some error, then print out the information
		// about the error
		fprintf(stderr,
			"Failed to load: %s at line %d, column %d\n",
			core_definition.ErrorDesc(),
			core_definition.ErrorRow(),
			core_definition.ErrorCol());
			
		return ERROR_SYNTAX;
	}
	
	free(xml_path);

	return RES_OK;	
}
int ResourceMap::getPinNumber(const char *name)
{
	const struct pin_entry* p=pin_table;
	while (p->pin_number>=0)
	{
		if (strcmp(name,p->name)==0)
			return p->pin_number;
		p++;
	}
	
	return -1;
}
uint8_t ResourceMap::getPinID(const char *name)
{
	const struct pin_entry* p=pin_table;
	while (p->pin_number>=0)
	{
		//DBG("%s == %s ? (%d)\n",name,p->name,strcmp(name,p->name));
		if (strcmp(name,p->name)==0)
			return p->id;
		p++;
	}
	return INVALID_PIN;
	
}


const char* ResourceMap::getPinName(uint8_t id)
{
	const struct pin_entry* p=pin_table;
	while (p->pin_number>=0)
	{
		if (p->id==id)
			return p->name;
		p++;
	}
	return "(UNKNOWN)";
}

Pin *ResourceMap::getPin(uint8_t gpio)
{
	return pins[gpio];
}


/*

void *ResourceMap::getSerial(int n)
{
}

void *ResourceMap::getSerial(pin rx, pin tx)
{
}


void *ResourceMap::getPWMDriver(pin pwm)
{
}

void *ResourceMap::getSPIDriver(pin cs, pin miso, pin mosi, pin sck)
{
}
*/

