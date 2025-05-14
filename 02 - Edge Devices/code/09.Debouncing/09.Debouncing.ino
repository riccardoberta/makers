int led_pin = 13;
int button_pin = 2;

volatile int count = 0;

// Timestamp of last valid button press
volatile unsigned long lastDebounceTime = 0; 

// Debounce delay in milliseconds
const unsigned long debounceDelay = 50; 

void handle_button() {
    // Check the time since the last valid button press
    unsigned long currentTime = millis();
    if (currentTime - lastDebounceTime > debounceDelay) {
        digitalWrite(led_pin, digitalRead(button_pin));

        // Print the count to the serial monitor
        count++;
        Serial.println(count);
        
        // Update the last debounce time
        lastDebounceTime = currentTime;
    }
}

void handle_other_stuff() {
    delay(250);
}

void setup() {
    Serial.begin(9600);
    pinMode(led_pin, OUTPUT);           
    pinMode(button_pin, INPUT_PULLUP);  
    attachInterrupt(INT0, handle_button, CHANGE);
}

void loop() {
    handle_other_stuff();
}
