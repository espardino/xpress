#!/bin/env python
from xpress import *

print "Hello Python!"

init()
setupHardware("core0")

pin_led = F39

pinMode(pin_led,OUTPUT)


while True:
	digitalWrite(pin_led,HIGH)
	delay(500)
	digitalWrite(pin_led,LOW)
	delay(500)



