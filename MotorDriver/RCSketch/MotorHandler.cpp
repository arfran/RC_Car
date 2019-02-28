#include "MotorHandler.h"




void MotorHandler::leftMotor(int duty){
  
	analogWrite(14,duty);
}

void MotorHandler::rightMotor(int duty){
	analogWrite(15,duty);
	
	
}

void MotorHandler::motorForward(int duty){
   digitalWrite(22,LOW); //1     11,12 control right motor
   digitalWrite(21,HIGH);  //0
   analogWrite(15,duty); //right motor
   digitalWrite(20,LOW);  //1    8,9 control left motor
   digitalWrite(19,HIGH);   //0
   analogWrite(14,duty); //left motor
   
   
}

void MotorHandler::motorReverse(int duty){
   digitalWrite(22,HIGH);  //0
   digitalWrite(21,LOW); //1
   analogWrite(15,duty); //right
   digitalWrite(20,HIGH);   //0
   digitalWrite(19,LOW);  //1
   analogWrite(14,duty); //left 
}

void MotorHandler::motorLeft(int duty){
   digitalWrite(22,HIGH);  //1
   digitalWrite(21,LOW);   //0
   //int t = duty/3;
   analogWrite(15,100); //right
   digitalWrite(20,LOW);    //1, make left wheels turn reverse for larger pivot
   digitalWrite(19,HIGH);    //0
   analogWrite(14,(duty)); //left; cut duty cycle by half to allow the car to effectively turn better

  
}

void MotorHandler::motorRight(int duty){

  digitalWrite(22,LOW); //1, make right wheel turn reverse for larger pivot
  digitalWrite(21,HIGH); //0
  analogWrite(15,(duty)); //right; cut duty cycle by half to allow the car to effectively turn better
  digitalWrite(20,HIGH); //1
  digitalWrite(19,LOW);  //0
  //int t = duty/3;
  analogWrite(14,100); //left

  
}


MotorHandler::MotorHandler(){
  pinMode(15,OUTPUT); //enable B pin, and motor pwm pin (controls speed)
  pinMode(22,OUTPUT); //H-Bridge pin IN4
  pinMode(21,OUTPUT); //H-Bridge pin IN3
  pinMode(14,OUTPUT);//enable A pin
  pinMode(20,OUTPUT); //IN2
  pinMode(19,OUTPUT); //IN1
  
}

void MotorHandler::motorStop(){
  analogWrite(14,0);
  analogWrite(15,0);

}
