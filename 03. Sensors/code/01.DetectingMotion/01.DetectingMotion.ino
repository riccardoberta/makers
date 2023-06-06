int pirPin = 2;
int count = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(pirPin, INPUT);
}

void loop() {
  int pirVal = digitalRead(pirPin);

  if(pirVal == HIGH) { 
    count++;
    Serial.print("Motion Detected: "); 
    Serial.println(count);

    // The sensor needs 2 seconds to take an 
    // image to compare to
    delay(2000); 
  }
}
