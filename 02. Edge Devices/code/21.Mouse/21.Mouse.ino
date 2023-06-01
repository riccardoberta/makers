#define potXPin 4
#define potYPin 5

void setup() {
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(potXPin);
  int y = analogRead(potYPin);
  
  Serial.print('M');
  Serial.print(",");
  Serial.print(x,DEC);
  Serial.print(",");
  Serial.print(y,DEC);
  Serial.print(",");
  Serial.println();  // send a cr/lf
  
  delay(50); // send position 20 times a second
}
