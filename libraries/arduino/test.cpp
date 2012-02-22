#include <WProgram.h>


void setupXpress()
{
	setupHardware("core0");
}

void setup()
{
	

	pinMode(F27,OUTPUT);
	pinMode(F39,OUTPUT);
	pinMode(F44,INPUT);
}

void loop()
{
	digitalWrite(F27,HIGH);
	delay(100);
	digitalWrite(F27,LOW);
	delay(100);
	
	if (digitalRead(F44)==HIGH)
	{
		digitalWrite(F39,LOW);
		
	}
	else
	{	
		digitalWrite(F39,HIGH);
	}
	
}
