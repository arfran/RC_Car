#include "Arduino.h"
class HCSR04{
	
	private:
		int triggerPin = 7;
    long startTime;
    long endTime;
		s_pin echoPin = 11;
    long cm;
    int state;
	public:
		void setTrigger();
		float ping();
    void echoChange();
    long getCm();
		HCSR04();
	
	
	
};
