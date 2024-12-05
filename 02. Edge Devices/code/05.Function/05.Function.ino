// Function

float average_reading(int sensor_pin, int size) 
{
  int i;
  float average;
  float sum;

  sum = 0.0;    // initial value of sum
  for (i=1; i<=size; i++) {
    sum = sum + analogRead(sensor_pin);
  }
  average = sum/size;
  
  return(average);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int n=15;
  int pot_pin=1;
  float reading;
  float voltage;

  reading = average_reading(pot_pin,n);
  voltage = reading*(5.0/1023.0);

  Serial.println(reading);
  Serial.println(voltage);
  Serial.println();
}

