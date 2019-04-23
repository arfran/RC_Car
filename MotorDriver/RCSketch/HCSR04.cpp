#include "HCSR04.h"

void HCSR04::setTrigger(){ // sends pulse to trigger to initiate reading
	digitalWrite(12, LOW);
	delayMicroseconds(5);
	digitalWrite(12, HIGH);
	delayMicroseconds(10);
	digitalWrite(12, LOW);
}

HCSR04::HCSR04(){
    this->inches = 0;
//  pinMode(this->echoPin, INPUT);
//  pinMode(this->triggerPin,OUTPUT);
}

long HCSR04::ping(){
	long duration = pulseIn(11,HIGH,1000000); //pulseIn(11,HIGH,1000)
  //Serial.println(duration);
  long test = (duration/2) / 74; // converts to inches
  //Serial.println(test);
	return test;
	
}

void HCSR04::echoChange(){
    switch(digitalRead(3)){
        
        case HIGH:
          this->endTime = 0;
          this->startTime = millis();
          break;

        case LOW:
          this->endTime = millis();
          //Serial.println(this->endTime);
          this->inches = ((this->endTime - this->startTime)*1000.0)/148.0;
          //this->inches = (this->endTime - this->startTime)*340.0/2.0;
          // Serial.println(this->inches);
          
          break;

        default:
          break;
    }

  
}
float HCSR04::getInches(){

  return this->inches;
}
float HCSR04::getStart(){
  return this->startTime;
}
float HCSR04::getEnd(){
  return this->endTime;
}
