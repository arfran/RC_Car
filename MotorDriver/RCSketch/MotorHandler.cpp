#include "MotorHandler.h"

/* PINS: 
 *  RightHB1, RightHB2 control right motor (01 forward 10 reverse)
 *  LeftHB1, LeftHB2 control left motor (01 forward 10 reverse)
 *  pin RightPWM is right motor duty cycle pin, pin LeftPWM is left motor duty cycle pin
 *  
*/
void MotorHandler::leftMotor(int duty){
  
	analogWrite(LeftPWM,duty);
}

void MotorHandler::rightMotor(int duty){
	analogWrite(RightPWM,duty);
	
}

void MotorHandler::motorForward(int duty){
   digitalWrite(RightHB2,LOW); //0     
   digitalWrite(RightHB1,HIGH);  //1
   digitalWrite(LeftHB2,LOW);  //0
   digitalWrite(LeftHB1,HIGH);   //1
   rightMotor(duty); //right motor
   leftMotor(duty); //left motor
   
   
}

void MotorHandler::motorReverse(int duty){
   digitalWrite(RightHB2,HIGH);  //1
   digitalWrite(RightHB1,LOW); //0
   digitalWrite(LeftHB2,HIGH);   //1
   digitalWrite(LeftHB1,LOW);  //0
   rightMotor(duty); //right
   leftMotor(duty); //left 
}

void MotorHandler::motorLeft(int duty){
   digitalWrite(RightHB2,HIGH);  //1
   digitalWrite(RightHB1,LOW);   //0
   digitalWrite(LeftHB2,LOW);    //0, make left wheels turn reverse for larger pivot
   digitalWrite(LeftHB1,HIGH);    //1
   rightMotor(duty); //right
   leftMotor(duty/2); //left; cut duty cycle by half to allow the car to effectively turn better

  
}

void MotorHandler::motorRight(int duty){

  digitalWrite(RightHB2,LOW); //0, make right wheel turn reverse for larger pivot
  digitalWrite(RightHB1,HIGH); //1
  digitalWrite(LeftHB2,HIGH); //1
  digitalWrite(LeftHB1,LOW);  //0
  rightMotor(duty/2); //right; cut duty cycle by half to allow the car to effectively turn better
  leftMotor(duty); //left

  
}


MotorHandler::MotorHandler(){
  pinMode(RightPWM,OUTPUT); //enable B pin, and motor pwm pin (controls speed)
  pinMode(RightHB2,OUTPUT); //H-Bridge pin IN4
  pinMode(RightHB1,OUTPUT); //H-Bridge pin IN3
  pinMode(LeftPWM,OUTPUT);//enable A pin
  pinMode(LeftHB2,OUTPUT); //IN2
  pinMode(LeftHB1,OUTPUT); //IN1
  
}

void MotorHandler::motorStop(){ // turns off pwm
  analogWrite(LeftPWM,0);
  analogWrite(RightPWM,0);

}
