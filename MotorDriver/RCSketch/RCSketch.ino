/* ECE 458
 * MotorDriver_v4_4_a
 * 
 * In this version: 
 * Modifications to accompany the change from the Arduino 101 microcontroller
 * to the Z-Uno development board
 * 
 * Written by Shaqueir Tardif, Aiden Gula, and Adam Francoeur
 * 3/21/2019
 */

#include "Arduino.h"
#include "MotorHandler.h"
#include "HCSR04.h"
#include <PID_v1.h>

//#include "ServoHandler.h"
int duty=0;
double leftmotorCounter=0;
double rightmotorCounter=0;
double dutyCycleLeft=255;
double dutyCycleRight=255;
double target = 200;
int i =0;
double targetLeftEncoder=0;
double targetRightEncoder=0;
long currentDistance=0;
byte dimmerValue=0;
//ServoHandler servoController(8);
int timeOut =0;
int pidTimer = 0;
int dutyCycle = 200;
double aggKp=4, aggKi=0.2, aggKd=1;
double leftTemp=0, rightTemp =0;
int echoFlag=0;
 
MotorHandler handler;
HCSR04 sensorHandler; // renames
ZUNO_SETUP_ISR_1MSTIMER(timer_handler);
ZUNO_SETUP_ISR_GPTIMER(pid_handler);

ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getter,setter));
ZUNO_SETUP_ISR_INT0(Encoder_handlerOne); //
ZUNO_SETUP_ISR_INT1(Encoder_handlerTwo); 

//ZUNO_SETUP_ISR_ZEROX(echoWrapper);
//PID mypid1(&leftmotorCounter,&dutyCycleLeft, &targetLeftEncoder,aggKp,aggKi,aggKd,DIRECT);
//PID mypid2(&rightmotorCounter, &dutyCycleRight, &targetRightEncoder, aggKp, aggKi, aggKd,DIRECT); 
//PID mypid1(&leftmotorCounter,&dutyCycleLeft, &rightmotorCounter,aggKp,aggKi,aggKd,DIRECT);
//PID mypid2(&rightmotorCounter, &dutyCycleRight, &leftmotorCounter, aggKp, aggKi, aggKd,DIRECT); 
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
        leftmotorCounter=0;
        rightmotorCounter=0;
        handler.motorLeft(dutyCycle);
        break;
      case 20:
          state = FORWARD;
          leftmotorCounter=0;
          rightmotorCounter=0;
          handler.motorForward(dutyCycle);
         
        break;
      case 30:
        state = RIGHT;
        leftmotorCounter=0;
        rightmotorCounter=0;
        handler.motorRight(dutyCycle);
        break;
      case 40:
        state = BACKWARD;
        leftmotorCounter=0;
        rightmotorCounter=0;
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
  //zunoExtIntMode(ZUNO_EXT_ZEROX,CHANGE);
  mypid1.SetMode(AUTOMATIC);
  mypid2.SetMode(AUTOMATIC);
  pinMode(11, INPUT);
  pinMode(12,OUTPUT);
  zunoGPTInit(ZUNO_GPT_CYCLIC); 
  zunoGPTEnable(1);
  zunoGPTSet(65000);
  
  //mypid1.SetOutputLimits(0,70);
  //mypid2.SetOutputLimits(0,70);
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
      
    
    
      
      if((leftmotorCounter >= 200  && rightmotorCounter >= 200) && (state == FORWARD || state == BACKWARD)) {
            
//            Serial.println(leftmotorCounter);
//            Serial.println(rightmotorCounter);
//            
              state = STOP;
              handler.motorStop();
              dimmerValue= 0;
              leftmotorCounter=0;
              rightmotorCounter=0;
            
      }
      if((leftmotorCounter >= 20 && rightmotorCounter >= 20) && (state == LEFT || state == RIGHT)){
            state = STOP;
            handler.motorStop();
            dimmerValue = 0;
            leftmotorCounter=0;
            rightmotorCounter=0;
      }
    if(state == FORWARD || state == BACKWARD){
        // mypid1.Compute();
         //mypid2.Compute();
         //(int)dutyCycleLeft
         handler.leftMotor(dutyCycleLeft);
         handler.rightMotor(dutyCycleRight);
            
         //float inches = sensorHandler.getInches();
//         if(currentDistance <= 5)
//         {
//            
//            state = STOP;
//            handler.motorStop();
//            dimmerValue = 0;
//            leftmotorCounter=0;
//            rightmotorCounter=0;
//          }

          


    }
}




    
  


void pid_handler(){

  if( (pidTimer == 2) &&( state == FORWARD || state == BACKWARD)){
       Serial.println("Hello");
     //  mypid1.Compute();
//      mypid2.Compute();
     pidTimer =0;
          
   }
   pidTimer++;
  
}

  


void timer_handler(){
   
   
   if(timeOut == 100){
        Serial.print("Motor Right: ");
        Serial.println(rightmotorCounter);
//        Serial.println(leftmotorCounter);
        Serial.print("Motor Left: ");
        Serial.println(leftmotorCounter);
//      sensorHandler.setTrigger();
//      currentDistance = sensorHandler.ping();
      
   }

  
   timeOut = (timeOut+1)%101;
}

void Encoder_handlerOne(){
    if(state == STOP){
      return;
    }
    leftTemp++;
    if((int)leftTemp % 20 ==0){
        leftmotorCounter++;

        leftTemp=0;
    }
    
    
  

}
void Encoder_handlerTwo(){
  if(state == STOP){
    return;
  }
    rightTemp++;
    if((int)rightTemp % 20 ==0){
      rightmotorCounter++;

      rightTemp =0;
    }

}


//
void echoWrapper(){

    sensorHandler.echoChange();
    //sensorHandler.ping();

}
