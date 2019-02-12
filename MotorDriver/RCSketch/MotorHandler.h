include "Arduino.h"

class MotorHandler{
  public:
    void leftMotor(int duty);
    void rightMotor(int duty);
	  void motorForward(int duty);
	  void motorReverse(int duty);
	  void motorLeft(int duty);
	  void motorRight(int duty);
    void motorStop();
	  MotorHandler();
    

   private:
    int LeftHB1 = 19;
    int LeftHB2 = 20;
    int RightHB1 = 21;
    int RightHB2 = 22;
    int LeftPWM = 14;
    int RightPWM = 15;
  
};
