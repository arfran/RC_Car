#include "Arduino.h"
class HCSR04{
	
	private:
		int triggerPin = 7;
    float startTime;
    float endTime;
		s_pin echoPin = 11;
    float inches;
    int state;
	public:
		void setTrigger();
		float ping();
    void echoChange();
    float getInches();
    float getStart();
    float getEnd();
		HCSR04();
	
	
	
};
