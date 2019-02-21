

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


#include "MotorHandler.h"
#include "HCSR04.h"
#include <PID_v1.h>

int duty=0;
double leftmotorCounter=0;
double rightmotorCounter = 0;
double dutyCycleLeft=200;
double dutyCycleRight=200;
float currentDistance;
byte dimmerValue=0;
int timeOut =0;
int dutyCycle = 200;
double aggKp=4, aggKi=0.2, aggKd=1;
MotorHandler handler;
HCSR04 sensorHandler;
ZUNO_SETUP_ISR_1MSTIMER(timer_handler);
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getter , setter));
ZUNO_SETUP_ISR_INT0(Encoder_handlerOne);
ZUNO_SETUP_ISR_INT1(Encoder_handlerTwo); 

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



void setter(byte newValue){
	  dimmerValue = newValue;
    switch(newValue){
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
        handler.motorForward(dutyCycle);
        break;
      case 30:
        state = RIGHT;
        handler.motorRight(dutyCycle);
        break;
      case 40:
        state = BACKWARD;
        handler.motorReverse(dutyCycle);
        break;
      default:
        break;
    }
    
}

byte getter(void){
    return dimmerValue;
}






void setup() {
  Serial.begin(9600);
  zunoExtIntMode(ZUNO_EXT_INT0, RISING);
  zunoExtIntMode(ZUNO_EXT_INT1, RISING);
  mypid1.SetMode(AUTOMATIC);
  mypid2.SetMode(AUTOMATIC);
  mypid1.SetOutputLimits(100,255);
  mypid2.SetOutputLimits(100,255);

  
  
  

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






<<<<<<< HEAD
void loop(){
    
    switch(state){
        case STOP:
            handler.motorStop();
            break;
        case LEFT:
            handler.motorLeft(255);
            break;
        case UP:
            handler.motorReverse(255); //inverted for some reason
            break;
        case RIGHT:
            handler.motorRight(255);
            break;
        case DOWN:
            handler.motorForward(255);//inverted for some reason
            break;
        default:
            break;
=======
void loop(){ //motor Sync Function
>>>>>>> ba81c7298560b37d7cd04ede532f6fcb0739104a

    if(state == FORWARD || state == BACKWARD){
      
    
       mypid1.Compute();
       mypid2.Compute();
       handler.leftMotor((int)dutyCycleLeft);
       handler.rightMotor((int)dutyCycleRight);
       Serial.print("Motor Left: ");
       Serial.print(leftmotorCounter);
       Serial.print(" ");
       Serial.println(dutyCycleLeft);
       Serial.print("Motor Right: ");
       Serial.print(rightmotorCounter);
       Serial.print(" ");
       Serial.println(dutyCycleRight);
    }

//	if(leftmotorCounter % 4 ==0){ //for every pass of the 4th encoder node
//			int diff = (leftmotorCounter - rightmotorCounter);
//			if(diff > 0){
//          dutyCycle += 1 * (diff+5); //will only increment by 1 during this run; wouldn't have much effect
//          if (dutyCycle > 255){
//              dutyCycle = 200;}
//          handler.rightMotor(dutyCycle);
//			}
//			else{
//			    dutyCycle += 1* (diff+5);
//          if (dutyCycle > 255){
//              dutyCycle = 200;}
//          handler.leftMotor(dutyCycle);
//			}
//	}



    
  




  
}

void timer_handler(){

//   if(timeOut == 10000){
//        Serial.print("Right Counter ");
//        Serial.println(((float)(leftmotorCounter/20))*6);
//        Serial.print("Left Counter ");
//        Serial.println(((float)(rightmotorCounter/20))*6);
//        timeOut = 0;
//        dutyCycle += 10;
//        if(dutyCycle >255)
//            dutyCycle = 200;
//        leftmotorCounter =0;
//        rightmotorCounter = 0;
//        handler.motorForward(dutyCycle);
//        
//   }
//   timeOut++;
    
    

//   }
//   timeOut = (timeOut+1)%301;
}

void Encoder_handlerOne(){
    leftmotorCounter ++;

}
void Encoder_handlerTwo(){
    rightmotorCounter ++;
  
}
