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

//#include <stdio.h>

#include "MotorHandler.cpp"
#include "HCSR04.cpp"
int duty=0;
//MotorHandler handle;
//HCSR04 sensorHandle;
byte dimmerValue=0;
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getter,setter));


void setter(byte newValue){
    dimmerValue = newValue;
}

byte getter(void){
    return dimmerValue;
}


typedef enum {
      LEFT = 10,
      UP = 20,
      RIGHT = 30,
      DOWN = 40
      
      
      

}controllerData;


/* const int PWM1 = 10; //left front motor
  const int PWM2 = 11; //right front motor
  const int PWM3 = 6; //left rear motor
  const int PWM4 = 9; //right rear motor*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(15,OUTPUT); //enable B pin, and motor pwm pin (controls speed)
  pinMode(22,OUTPUT); //H-Bridge pin IN4
  pinMode(21,OUTPUT); //H-Bridge pin IN3
  pinMode(14,OUTPUT);//enable A pin
  pinMode(20,OUTPUT); //IN2
  pinMode(19,OUTPUT); //IN1
//  handle = new MotorHandler();
//  sensorHandle = new HCSR04();
  

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






void loop() {

  

}

