#include "Arduino.h"
class HCSR04{
	
	private:
		int triggerPin;
		int echoPin;
	public:
		void setTrigger();
		float ping();
		HCSR04();
	
	
	
};
