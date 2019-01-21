#include "MotorHandler.h"

MotorHandler::MotorHandler(){
  pinMode(11,OUTPUT);
  
}


void MotorHandler::motorForward(int duty){
   digitalWrite(22,HIGH); //1     11,12 control right motor
   digitalWrite(21,LOW);  //0
   analogWrite(15,duty); //right motor
   digitalWrite(20,HIGH);  //1    8,9 control left motor
   digitalWrite(19,LOW);   //0
   analogWrite(14,duty); //left motor
   
   
}

void MotorHandler::motorReverse(int duty){
   digitalWrite(22,LOW);  //0
   digitalWrite(21,HIGH); //1
   analogWrite(15,duty); //right
   digitalWrite(20,LOW);   //0
   digitalWrite(19,HIGH);  //1
   analogWrite(14,duty); //left 
}

void MotorHandler::motorLeft(int duty){
   digitalWrite(22,HIGH);  //1
   digitalWrite(21,LOW);   //0
   analogWrite(15,duty); //right
   digitalWrite(20,LOW);    //1, make left wheels turn reverse for larger pivot
   digitalWrite(19,HIGH);    //0
   analogWrite(14,(int)(duty/2)); //left; cut duty cycle by half to allow the car to effectively turn better

  
}

void MotorHandler::motorRight(int duty){

  digitalWrite(22,LOW); //1, make right wheel turn reverse for larger pivot
  digitalWrite(21,HIGH); //0
  analogWrite(15,(int)(duty/2)); //right; cut duty cycle by half to allow the car to effectively turn better
  digitalWrite(20,HIGH); //1
  digitalWrite(19,LOW);  //0
  analogWrite(14,duty); //left

  
}
