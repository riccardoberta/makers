#include <Wire.h>

const char HEADER = 'H';
int tmp102Address = 0x48;
int led1Pin = 6;
int led2Pin = 7;
int pirPin = 2;
int lightPin = 0;

void setup()
{
  Serial.begin(9600);
  
  Wire.begin();
  
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(pirPin,  INPUT);
}

void loop()
{
  float temperature = getTemperature();
  int motion = getMovement();
  float light = getLight();

  Serial.print(HEADER);
  Serial.print(";");
  Serial.print(temperature);
  Serial.print(";");
  Serial.print(motion);
  Serial.print(";");
  Serial.print(light);
  Serial.println(";");

  if (Serial.available() ) 
  {
    char ch = Serial.read();
    if(ch == '0')
      setLed(1,0);
    else if(ch == '1')
      setLed(1,1); 
    else if(ch == '2')
      setLed(2,0);
    else if(ch == '3')
      setLed(2,1);
  }
   
  delay(1000); 
}

void setLed(int led, int value)
{
  if(led == 1 && value == 1)
    digitalWrite(led1Pin,HIGH);
  if(led == 1 && value == 0)
    digitalWrite(led1Pin,LOW);

  if(led == 2 && value == 1)
    digitalWrite(led2Pin,HIGH);
    
  if(led == 2 && value == 0)
    digitalWrite(led2Pin,LOW);
}

float getLight()
{
  return  analogRead(lightPin); 
}
int getMovement()
{
  int pirVal = digitalRead(pirPin);

  if(pirVal == LOW)
    return 1;
  else
    return 0;
}

float getTemperature()
{
  Wire.requestFrom(tmp102Address,2); 
  byte MSB = Wire.read();
  byte LSB = Wire.read();
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 
  float celsius = TemperatureSum*0.0625;
  return celsius;
}
