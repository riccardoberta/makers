const int RED_PIN = 10;
const int YELLOW_PIN = 9;
const int GREEN_PIN = 8;

void setup() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RED_PIN, false);
  digitalWrite(YELLOW_PIN, false);
  digitalWrite(GREEN_PIN, true);
  delay(500);  

  digitalWrite(RED_PIN, false);
  digitalWrite(YELLOW_PIN, true);
  digitalWrite(GREEN_PIN, false);
  delay(500);

  digitalWrite(RED_PIN, true);
  digitalWrite(YELLOW_PIN, false);
  digitalWrite(GREEN_PIN, false);
  delay(500);
}
