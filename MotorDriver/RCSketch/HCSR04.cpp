#include "HCSR04.h"

void HCSR04::setTrigger(){
	digitalWrite(this->triggerPin, LOW);
	delayMicroseconds(5);
	digitalWrite(this->triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->triggerPin, LOW);
	
	
	
}

HCSR04::HCSR04(){
	this->triggerPin = 12;
	this->echoPin = 11;
  pinMode(this->echoPin, INPUT);
  pinMode(this->triggerPin,OUTPUT);
	
}

float HCSR04::ping(){
	
	long duration = pulseIn(this->echoPin,HIGH,1000000);
	return (duration/2) / 74;
	
}
