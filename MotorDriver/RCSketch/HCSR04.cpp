#include "HCSR04.h"

void HCSR04::setTrigger(){ // sends pulse to trigger to initiate reading
	digitalWrite(12, LOW);
	delayMicroseconds(5);
	digitalWrite(12, HIGH);
	delayMicroseconds(10);
	digitalWrite(12, LOW);
}

HCSR04::HCSR04(){
    this->cm = 0;
//  pinMode(this->echoPin, INPUT);
//  pinMode(this->triggerPin,OUTPUT);
}

float HCSR04::ping(){
	long duration = pulseIn(11,HIGH,1000);
	return (duration/2) / 74; // converts to inches
	
}

void HCSR04::echoChange(){
    if(!state){
        this->startTime = millis();  
        state++;    
    }
    else{
       this->endTime = millis();
       this->cm = ((endTime-startTime)/2)/74;
       state--;
    }

  
}
long HCSR04::getCm(){

  return this->cm;
}
