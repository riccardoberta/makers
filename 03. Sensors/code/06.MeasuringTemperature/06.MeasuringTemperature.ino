#include <Wire.h>

int tmp102Address = 0x48;

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  float celsius = getTemperature();
  Serial.print("Celsius: ");
  Serial.println(celsius);

  //just here to slow down the output
  delay(200); 
}

float getTemperature() {
  Wire.requestFrom(tmp102Address, 2);

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  // it's a 12 bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 
  float celsius = TemperatureSum*0.0625;

  return celsius;
}
