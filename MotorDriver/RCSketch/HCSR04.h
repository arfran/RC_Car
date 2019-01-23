#include "Arduino.h"
class HCSR04{
	
	private:
		int triggerPin;
		s_pin echoPin;
	public:
		void setTrigger();
		float ping();
		HCSR04();
	
	
	
};
