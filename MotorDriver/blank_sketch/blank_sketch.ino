ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(getter , setter));
byte dimmer Value;
void setup() {
  // put your setup code here, to run once:
  

}

void loop() {
  // put your main code here, to run repeatedly:

}

byte getter(){
  return dimmerValue;
}

void setter(byte newValue){
  dimmerValue =  newValue;
}
