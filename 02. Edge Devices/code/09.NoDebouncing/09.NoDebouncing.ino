// A push button as an input that toggles the state of the onboard LED

// Connect the push button to pin 2
const int PB_PIN = 2;

// Uses the onboard LED on pin 13
const int LED_PIN = 13;

// Flag to indicate the state of the push button
boolean buttonAlreadyPressed = false;

// Flag to indicate the state of the LED
boolean ledOn = false;

void setup()
{
    pinMode(PB_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (digitalRead(PB_PIN) == LOW)
  {
    // If the button was just been pressed
    if (!buttonAlreadyPressed)
    {
      // Sets the button's flag
      buttonAlreadyPressed = true;
      
      // Toggles the state of the LED
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn);
    }
  }
  else
  {
    // The button has been released
    buttonAlreadyPressed = false;
  }
}
