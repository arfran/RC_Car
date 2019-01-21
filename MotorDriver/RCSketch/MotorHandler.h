#include "Arduino.h"

class MotorHandler{
  public:
	  void motorForward(int duty);
	  void motorReverse(int duty);
	  void motorLeft(int duty);
	  void motorRight(int duty);
	  MotorHandler();

   private:
    int M1HB1;
    int M1HB2;
    int M2HB1;
    int M2HB2;
    int M1PWM;
    int M2PWM;
    


  
};
