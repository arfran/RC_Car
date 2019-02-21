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

int duty=0;
float leftmotorCounter=0;
float rightmotorCounter = 0;

byte dimmerValue=0;
int timeOut =0;

typedef enum {
      STOP = 0,
      LEFT = 10,
      UP = 20,
      RIGHT = 30,
      DOWN = 40
      
      
      

}Action;
MotorHandler handler;
HCSR04 sensorHandler;
ZUNO_SETUP_ISR_1MSTIMER(timer_handler);
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getter , setter));
ZUNO_SETUP_ISR_INT0(Encoder_handlerOne);
ZUNO_SETUP_ISR_INT1(Encoder_handlerTwo);
ZUNO_SETUP_ISR_ZEROX(Encoder_reset);

Action state;
void setter(byte newValue){
    dimmerValue = newValue;
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
  zunoExtIntMode(ZUNO_EXT_INT0, RISING);
  zunoExtIntMode(ZUNO_EXT_INT1, RISING);
  zunoExtIntMode(ZUNO_EXT_ZEROX, RISING);
  
  
  

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

      
    }
    
    //delay(2000);
    Serial.print("Left Motor: ");
    Serial.println(leftmotorCounter);
    Serial.print("Right Motor:");
    Serial.println(rightmotorCounter);

    
  




  
}

void timer_handler(){

   if(timeOut == 300){
      sensorHandler.setTrigger();
      //Serial.println(sensorHandler.ping());
   }
   timeOut = (timeOut+1)%301;
}

void Encoder_handlerOne(){
    leftmotorCounter += (1.00/20.00);

}
void Encoder_handlerTwo(){
    rightmotorCounter +=(1.00/20.00);
  
}

void Encoder_reset(){
//  if (leftmotorCounter == 10.00){
//    leftmotorCounter = 0.00;
//    rightmotorCounter = 0.00;

  
  if(leftmotorCounter == 10.00 && state == UP || state == DOWN){
  
  handler.motorStop();
  leftmotorCounter = 0.00;
  rightmotorCounter = 0.00;
  
  }
 
}
