#include "ServoHandler.h"

// global data
word g_ServoHandler_open;
word g_ServoHandler_close;
byte g_ServoHandler_state;
byte pin = 8;



#define ServoHandler_STATE_CLOSED 		0
#define ServoHandler_STATE_OPENED 		1

#define ServoHandler_DEG000_INTERVAL	2180
#define ServoHandler_DEG180_INTERVAL	9560

#define ServoHandler_OFFWHOLE_INTERVAL 40000  
#define ServoHandler_OFFREST_INTERVAL  40000 // 10ms in the end of interval  8

ZUNO_SETUP_ISR_GPTIMER(ServoHandler_gpt_handler);

ServoHandler::ServoHandler(byte p1)
{
	pin = p1;

	g_ServoHandler_open = ServoHandler_DEG000_INTERVAL;
	g_ServoHandler_close = ServoHandler_OFFWHOLE_INTERVAL - ServoHandler_DEG000_INTERVAL;
	g_ServoHandler_state = 0;

}

void ServoHandler::begin()
{

	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	
	g_ServoHandler_state = 2;

	zunoGPTInit(ZUNO_GPT_CYCLIC);	
  	zunoGPTSet(800); 
  	zunoGPTEnable(1); 
  	zunoGPTSet(g_ServoHandler_open); 


}
void ServoHandler::end()
{
	zunoGPTEnable(0); 
}
void ServoHandler::setValue(word value)
{
	value *= ((ServoHandler_DEG180_INTERVAL - ServoHandler_DEG000_INTERVAL) / 180);
	value += ServoHandler_DEG000_INTERVAL;
	g_ServoHandler_open = value;
	g_ServoHandler_close = ServoHandler_OFFWHOLE_INTERVAL - value;
	
}
void ServoHandler::setValueRAW(word value)
{
	value /= 4;
	g_ServoHandler_open = value;
	g_ServoHandler_close = ServoHandler_OFFWHOLE_INTERVAL - value;
}

void ServoHandler_gpt_handler()
{
	g_ServoHandler_state ++;
	switch((g_ServoHandler_state % 3))
	{
		case 0:
			digitalWrite(pin, HIGH);
			zunoGPTSet(g_ServoHandler_close); 
			break;
		case 1:
			digitalWrite(pin, LOW);
			zunoGPTSet(ServoHandler_OFFREST_INTERVAL);
			break;
		case 2:
			zunoGPTSet(g_ServoHandler_open); 
			break;
	}	

}