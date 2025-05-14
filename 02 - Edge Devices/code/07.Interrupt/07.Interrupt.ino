// Define the pin with the LED (the one on the board)
int led_pin = 13;

// Define the pin with the button
int button_pin = 2;

// Function to handle the button input and control the LED
void handle_button() {
    // Read the button and set the LED accordingly
    digitalWrite(led_pin, digitalRead(button_pin));
}

// Function to handle other tasks that take time
void handle_other_stuff() {
    // Simulate a delay for a long-running task
    delay(250);
}

void setup() {
    pinMode(led_pin, OUTPUT);
    pinMode(button_pin, INPUT_PULLUP);
    attachInterrupt(INT0, handle_button, CHANGE);
}

void loop() {
    handle_other_stuff();
}
