// Iterrupt 

int LED = 13;
int SW = 2;

void handleSW() {   
    digitalWrite(LED, digitalRead(SW));
}

void handleOtherStuff() {
    delay(250);
}

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(SW, INPUT_PULLUP);
    attachInterrupt(INT0, handleSW, CHANGE);
}

void loop() {
    handleOtherStuff();
}
