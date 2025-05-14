// define the pin that the sensor is attached to
int pir_pin = 2;

// a variable to count the number of times the sensor has been triggered
int count = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(pir_pin, INPUT);
}

void loop() {

  // detect the output of the sensor
  int pir_val = digitalRead(pir_pin);

  // if the sensor is triggered, increment the count
  if(pir_val == HIGH) { 
    count++;

    // send the count to the serial port
    Serial.print("Motion Detected: "); 
    Serial.println(count);

    // The sensor needs 2 seconds before it can detect motion again
    delay(2000); 
  }
}
