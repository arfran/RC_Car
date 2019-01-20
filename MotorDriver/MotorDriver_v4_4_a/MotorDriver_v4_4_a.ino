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
#include <string.h>
#include "MotorHandler.cpp"
int duty;
MotorHandler handle;
byte dimmerValue;
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getter,setter));

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


void motorWrite(int PWM, int dutyCycle) { //write to the 4 motors
  //const int PWM1 = 10; //left front motor
  //const int PWM2 = 11; //right front motor
  //const int PWM3 = 12; //left rear motor
  //const int PWM4 = 13; //right rear motor
  int PWM_outpin = PWM;
  analogWrite(PWM, dutyCycle);
  //analogWrite(PWM2,dutyCycle);
  //analogWrite(PWM3,dutyCycle);
  //analogWrite(PWM4,dutyCycle);

}



void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Input which function to run from the following options: \n");
  Serial.print("forward, reverse, right, left \n");
  
  
  
  //motorWrite(13, 255); //figure out a way to reverse the direction ---- 150 = medium speed, 255 = max

    while(!Serial.available());

    
    if(Serial.available()){
        String s = Serial.readString();
        if(s != "forward" && s != "left" && s!="right" && s!="reverse"){
            Serial.println("Not Understood\n");
            
        }
        else{
          Serial.println("Enter desired duty cycle (enter value from 0 - 255): ");
          while(!Serial.available());
          duty = Serial.parseInt();
          Serial.parseInt();
        }
        
          if(s == "forward"){
              Serial.println("Forward function executing at: ");
              Serial.print(duty);
              Serial.println("\n");
                digitalWrite(22,HIGH); //1     11,12 control right motor
                digitalWrite(21,LOW);  //0
                analogWrite(15,duty); //right motor
                digitalWrite(20,HIGH);  //1    8,9 control left motor
                digitalWrite(19,LOW);   //0
                analogWrite(14,duty); //left motor
                delay(5000);

                  //brake, stop
                digitalWrite(22,LOW); //right
                digitalWrite(21,LOW);
                digitalWrite(20,LOW); //left
                digitalWrite(19,LOW);
                delay(2000);

                Serial.println("Forward function Completed.\n");
              
          }
          else if(s == "reverse"){
        
              Serial.println("Reverse function executing at: ");
              Serial.print(duty);
              Serial.println("\n");
                //reverse
                digitalWrite(22,LOW);  //0
                digitalWrite(21,HIGH); //1
                analogWrite(15,duty); //right
                digitalWrite(20,LOW);   //0
                digitalWrite(19,HIGH);  //1
                analogWrite(14,duty); //left
                delay(5000); 


                 //brake, stop
                digitalWrite(22,LOW); //right
                digitalWrite(21,LOW);
                digitalWrite(20,LOW); //left
                digitalWrite(19,LOW);
                delay(2000);

              Serial.println("Reverse function Completed.\n");
              
          }
          else if(s =="left"){
            Serial.println("Left function executing at: ");
            Serial.print(duty);
            Serial.println("\n");
            //left --- right motor moves forward, left motor in a slower reverse direction
            digitalWrite(22,HIGH);  //1
            digitalWrite(21,LOW);   //0
            analogWrite(15,duty); //right
            digitalWrite(20,LOW);    //1, make left wheels turn reverse for larger pivot
            digitalWrite(19,HIGH);    //0
            analogWrite(14,(int)(duty/2)); //left; cut duty cycle by half to allow the car to effectively turn better
            delay(2000);
          

                 //brake, stop
                digitalWrite(22,LOW); //right
                digitalWrite(21,LOW);
                digitalWrite(20,LOW); //left
                digitalWrite(19,LOW);
                delay(2000);
              
             Serial.println("Left function Completed.\n");
            //analogWrite(3,100);//analogWrite(pin#,0-255)
            
          }
          else if(s == "right"){
              Serial.println("Right function executing at: ");
              Serial.print(duty);
              Serial.println("\n");

              //right --- left motor moves forward, right moves in reverse direction at slower rate
                digitalWrite(22,LOW); //1, make right wheel turn reverse for larger pivot
                digitalWrite(21,HIGH); //0
                analogWrite(15,(duty/2)); //right; cut duty cycle by half to allow the car to effectively turn better
                digitalWrite(20,HIGH); //1
                digitalWrite(19,LOW);  //0
                analogWrite(14,duty); //left
                delay(2000);
              

                  //brake, stop
                digitalWrite(22,LOW); //right
                digitalWrite(21,LOW);
                digitalWrite(20,LOW); //left
                digitalWrite(19,LOW);
                delay(2000);
                
              Serial.println("Right function Completed.\n");
          }

        }

}

void setter(byte newValue){
    dimmerValue = newValue;
}

byte getter(void){
    return dimmmerValue;
}
