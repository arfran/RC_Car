

#include "Arduino.h"

class ServoHandler
{

	public:
		ServoHandler(byte p1);
		void begin();
		void end();
		void setValue(word value);
		void setValueRAW(word value);
	private:
		byte my_data;
};

