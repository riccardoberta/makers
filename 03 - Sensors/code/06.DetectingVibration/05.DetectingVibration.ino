// the analog pin connected to the sensor
const int sensorPin = 0;
int count = 0;
const int THRESHOLD = 10;

void setup() {
   Serial.begin(9600);
}

void loop() {
  int val = analogRead(sensorPin);

  if (val >= THRESHOLD){
    count++;
    Serial.print("Vibration detected: ");
    Serial.println(count);
    delay(200);
  }
}
    
