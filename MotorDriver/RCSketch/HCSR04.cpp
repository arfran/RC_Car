#include "HCSR04.h"

void HCSR04::setTrigger(){ // sends pulse to trigger to initiate reading
	digitalWrite(this->triggerPin, LOW);
	delayMicroseconds(5);
	digitalWrite(this->triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->triggerPin, LOW);
}

HCSR04::HCSR04(){
  pinMode(this->echoPin, INPUT);
  pinMode(this->triggerPin,OUTPUT);
}

float HCSR04::ping(){
	
	long duration = pulseIn(this->echoPin,HIGH);
	return (duration/2) / 74; // converts to inches
	
}
