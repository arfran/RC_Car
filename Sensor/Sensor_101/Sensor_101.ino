int ADC0 = 3;     
int ADC1 = 4;      
int ADC2 = 5; 
int ADC3 = 6; 

int val = 0;       

void setup()
{
  Serial.begin(9600);         
}

void loop()
{
  val = analogRead(ADC0);     
  Serial.println(val);        
  
   val = analogRead(ADC1);    
  Serial.println(val);        
  
   val = analogRead(ADC2);    
  Serial.println(val);        
  
   val = analogRead(ADC3);    
  Serial.println(val);        
  
}
