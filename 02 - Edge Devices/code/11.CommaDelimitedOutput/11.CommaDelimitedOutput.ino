void setup() {
  Serial.begin(9600);
}

void loop() {
  // Simulated sensor readings
  float temperature = 25.3;
  float humidity = 60.1;
  float pressure = 1013.2;

  // Send a comma-delimited message with a header
  Serial.print('H'); 
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print(pressure);
  Serial.print(",");  
  Serial.println();

  // Wait before sending the next message
  delay(100);
}