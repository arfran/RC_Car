#include "HCSR04.h"

void HCSR04::setTrigger(){ // sends pulse to trigger to initiate reading
	digitalWrite(12, LOW);
	delayMicroseconds(5);
	digitalWrite(12, HIGH);
	delayMicroseconds(10);
	digitalWrite(12, LOW);
}

HCSR04::HCSR04(){
//  pinMode(this->echoPin, INPUT);
//  pinMode(this->triggerPin,OUTPUT);
}

float HCSR04::ping(){
	//long duration = pulseIn(this->echoPin,HIGH,100000);
	long duration = pulseIn(11,HIGH,1000000);
	return (duration/2) / 74; // converts to inches
	
}
