int led_pin = 13;
int button_pin = 2;

// Add a variable to count the number of times the button is pressed
// to observe the bouncing problem
volatile int count = 0;

void handle_button() {
    digitalWrite(led_pin, digitalRead(button_pin));

    // Increment the count each time the button is pressed
    count++;

    // Print the count to the serial monitor
    Serial.println(count);
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