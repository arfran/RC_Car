#include "Arduino.h"
class HCSR04{
	
	private:
		int triggerPin = 12;
		s_pin echoPin = 11;
	public:
		void setTrigger();
		float ping();
		HCSR04();
	
	
	
};
