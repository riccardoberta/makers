// Define the pin with the LED (the one on the board)
int led_pin = 13;

// define the pin with the button
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
    // Set LED pin as output
    pinMode(led_pin, OUTPUT);
    // Set button pin as input with internal pull-up resistor
    pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
    // Check the button and update LED
    handle_button();

    // Perform other tasks (with delay)
    handle_other_stuff();
}