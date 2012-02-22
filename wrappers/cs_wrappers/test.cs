using  System;
using hw = Espardino.Xpress;

public class test {

	static void Main() {
	
		int pinLed = hw.F39;
		
		Console.WriteLine("Hello C#!");
		hw.init();
		hw.setupHardware("core0");
		hw.pinMode(pinLed,hw.OUTPUT);
		
		while(true)
		{
			hw.digitalWrite(pinLed,hw.HIGH);
			hw.delay(500);
			hw.digitalWrite(pinLed,hw.LOW);
			hw.delay(500);
		}
	
	}
}
