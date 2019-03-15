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
	
<<<<<<< HEAD
	long duration = pulseIn(this->echoPin,HIGH,100000);
=======
	long duration = pulseIn(this->echoPin,HIGH,1000000);
>>>>>>> 4eb64726bb7661b0cd061529461db54a8a7eb7d2
	return (duration/2) / 74; // converts to inches
	
}
