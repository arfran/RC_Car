/* ECE 458
 * MotorDriver_v4_4_a
 * 
 * In this version: 
 * Modifications to accompany the change from the Arduino 101 microcontroller
 * to the Z-Uno development board
 * 
 * Written by Shaqueir Tardif
 * 1/17/2019
 */


#include "MotorHandler.h"
#include "HCSR04.h"

int duty=0;

byte dimmerValue=0;

typedef enum {
      STOP = 0,
      LEFT = 10,
      UP = 20,
      RIGHT = 30,
      DOWN = 40
      
      
      

}Action;
MotorHandler handler;
HCSR04 sensorHandler;
//ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getter,setter));

Action state;
void setter(byte newValue){
    switch(newValue){
      case 0:
        state = STOP;
        break;
      case 10:
        state = LEFT;
        break;
      case 20:
        state = UP;
        break;
      case 30:
        state = RIGHT;
        break;
      case 40:
        state = DOWN;
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
//  pinMode(15,OUTPUT); //enable B pin, and motor pwm pin (controls speed)
//  pinMode(22,OUTPUT); //H-Bridge pin IN4
//  pinMode(21,OUTPUT); //H-Bridge pin IN3
//  pinMode(14,OUTPUT);//enable A pin
//  pinMode(20,OUTPUT); //IN2
//  pinMode(19,OUTPUT); //IN1
  
  
  

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






void loop(){

    switch(state){
        case STOP:
            break;
        case LEFT:
            handler.motorLeft(255);
            break;
        case UP:
            handler.motorForward(255);
            break;
        case RIGHT:
            handler.motorRight(255);
            break;
        case DOWN:
            handler.motorReverse(255);
            break;
        default:
            break;

      
    }
  

  



  
}

