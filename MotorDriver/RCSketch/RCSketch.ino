/* ECE 458
 * MotorDriver_v4_4_a
 * 
 * In this version: 
 * Modifications to accompany the change from the Arduino 101 microcontroller
 * to the Z-Uno development board
 * 
 * Written by Shaqueir Tardif and Aiden Gula
 * 1/17/2019
 */

#include "Arduino.h"
#include "MotorHandler.h"
#include "HCSR04.h"
#include <PID_v1.h>
#include <ZUNO_SERVO.h>

int duty=0;
double leftmotorCounter=0;
double rightmotorCounter = 0;
double dutyCycleLeft=255;
double dutyCycleRight=255;
double targetLeftEncoder = 0;
double targetRightEncoder = 0;
float currentDistance;
byte dimmerValue=0;
int timeOut =0;
int dutyCycle = 200;
double aggKp=4, aggKi=0.2, aggKd=1;
double leftTemp=0, rightTemp =0;
ServoController servo(16); // PWM1 pin
MotorHandler handler;
HCSR04 sensorHandler;
ZUNO_SETUP_ISR_1MSTIMER(timer_handler);
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getter , setter));
ZUNO_SETUP_ISR_INT0(Encoder_handlerOne); //
ZUNO_SETUP_ISR_INT1(Encoder_handlerTwo); 
//
//PID mypid1(&leftmotorCounter,&dutyCycleLeft, &targetLeftEncoder,aggKp,aggKi,aggKd,DIRECT);
//PID mypid2(&rightmotorCounter, &dutyCycleRight, &targetRightEncoder, aggKp, aggKi, aggKd,DIRECT); 
PID mypid1(&leftmotorCounter,&dutyCycleLeft, &rightmotorCounter,aggKp,aggKi,aggKd,DIRECT);
PID mypid2(&rightmotorCounter, &dutyCycleRight, &leftmotorCounter, aggKp, aggKi, aggKd,DIRECT); 
typedef enum{
  FORWARD= 20,
  BACKWARD=40,
  LEFT = 10,
  RIGHT = 30,
  STOP = 0
}Action;

Action state;

float getter(void){
  return dimmerValue;
  
}

void setter(byte newValue){
	  dimmerValue = newValue;
    switch(dimmerValue){
      case 0:
          state = STOP;
          handler.motorStop();
          leftmotorCounter=0;
          rightmotorCounter=0;
        break;
      case 10:
        state = LEFT;
        handler.motorLeft(dutyCycle);
        break;
      case 20:
          state = FORWARD;
//        targetLeftEncoder += 300;
//        targetRightEncoder += 300;
          handler.motorForward(dutyCycle);
          Serial.print("Forward: ");
          Serial.println(dutyCycle);
        break;
      case 30:
        state = RIGHT;
        handler.motorRight(dutyCycle);
        break;
      case 40:
        state = BACKWARD;
//        targetLeftEncoder += 300;
//        targetRightEncoder += 300;
        handler.motorReverse(dutyCycle);
        break;
      default:
        break;
    }
    
}







void setup() { 
  Serial.begin(9600);
  zunoExtIntMode(ZUNO_EXT_INT0,RISING);
  zunoExtIntMode(ZUNO_EXT_INT1,RISING);
  mypid1.SetMode(AUTOMATIC);
  mypid2.SetMode(AUTOMATIC);
  pinMode(11, INPUT);
  pinMode(12,OUTPUT);
//  mypid1.SetOutputLimits(50,255);
//  mypid2.SetOutputLimits(50,255);
//  

  
  
  

}
  

  /*
   *****H-Bridge Input Table*************
   
          0 - IN3 0 - IN4 Brake ---- pin12 for IN3; pin 13 for IN4
          0 - IN3 1 - IN4 Forward
          1 - IN3 0 - IN4 Reverse
          1 - IN3 1 - IN4 Brake
  ****************************************
  */

    /*
   *****H-Bridge Input Table*************
   
          0 - IN1 0 - IN2 Brake ---- pin10 for IN1; pin 11 for IN2
          0 - IN1 1 - IN2 Forward
          1 - IN1 0 - IN2 Reverse
          1 - IN1 1 - IN2 Brake
  ****************************************
  */






void loop(){ //motor Sync Function
    Serial.println(currentDistance);
    if(state == FORWARD || state == BACKWARD){
      
      
         
//         handler.leftMotor((int)dutyCycleLeft);
//         handler.rightMotor((int)dutyCycleRight);
         
         if(currentDistance <= 7.00)
         {
            handler.motorStop();
            state = STOP;
            dimmerValue = 0;
            leftmotorCounter=0;
            rightmotorCounter=0;
          }
//         Serial.print("Motor Left: ");
//         Serial.print(leftmotorCounter);
//         Serial.print(" ");
//         Serial.println(dutyCycleLeft);
//         Serial.print("Motor Right: ");
//         Serial.print(rightmotorCounter);
//         Serial.print(" ");
//         Serial.println(dutyCycleRight);


    }
}




    
  




  


void timer_handler(){
   float distance;
   if(timeOut == 100){
      distanceCheck();
   }
   timeOut++;
  
   timeOut = (timeOut+1)%101;
}

void Encoder_handlerOne(){
    leftTemp++;
    if((int)leftTemp % 20 ==0){
      leftmotorCounter++;
      leftTemp=0;
    }
    
  

}
void Encoder_handlerTwo(){
    rightTemp++;
    if((int)rightTemp % 20 ==0){
      rightmotorCounter++;
      rightTemp =0;
    }

}

void distanceCheck()
{
  mypid1.Compute();
  mypid2.Compute();
  sensorHandler.setTrigger();
  currentDistance = sensorHandler.ping();
//  Serial.println(currentDistance);

 
}
