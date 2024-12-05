const int L1_RED_PIN = 8;
const int L1_YELLOW_PIN = 9;
const int L1_GREEN_PIN = 10;

const int L2_RED_PIN = 11;
const int L2_GREEN_PIN = 12;

const int BUTTON_PIN = 2;

volatile int request = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  pinMode(L1_RED_PIN, OUTPUT);
  pinMode(L1_YELLOW_PIN, OUTPUT);
  pinMode(L1_GREEN_PIN, OUTPUT);
  pinMode(L2_RED_PIN, OUTPUT);
  pinMode(L2_GREEN_PIN, OUTPUT);

  attachInterrupt(0,changeLight,RISING);
  
  digitalWrite(L1_RED_PIN, LOW);
  digitalWrite(L1_YELLOW_PIN, LOW);
  digitalWrite(L1_GREEN_PIN, HIGH);
  
  digitalWrite(L2_RED_PIN, HIGH);
  digitalWrite(L2_GREEN_PIN, LOW);

  request = false;
}

void loop() 
{

  digitalWrite(L2_RED_PIN, HIGH);
  digitalWrite(L1_RED_PIN, LOW);
  digitalWrite(L1_YELLOW_PIN, LOW);
  digitalWrite(L1_GREEN_PIN, HIGH);
  delay(1000);  


  digitalWrite(L2_RED_PIN, HIGH);
  digitalWrite(L1_RED_PIN, LOW);
  digitalWrite(L1_YELLOW_PIN, HIGH);
  digitalWrite(L1_GREEN_PIN, LOW);
  delay(1000);

  digitalWrite(L1_RED_PIN, HIGH);
  digitalWrite(L1_YELLOW_PIN, LOW);
  digitalWrite(L1_GREEN_PIN, LOW);
  delay(1000);
  
  if (request == true) {
    digitalWrite(L2_RED_PIN, LOW);
    digitalWrite(L2_GREEN_PIN, HIGH);
    delay(1000);

    digitalWrite(L2_RED_PIN, HIGH);
    digitalWrite(L2_GREEN_PIN, LOW);
    delay(1000);  

    request = false;
  }
}

void changeLight() {
  request = true;
}


