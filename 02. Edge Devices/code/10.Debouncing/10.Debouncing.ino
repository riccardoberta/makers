// A push button as an input that toggles the state of the onboard LED
// A software switch debouncing process is implemented

// We are going to take two measurements, one in the beginning of the signal 
// transition, and one after the transient period has passed. 
// Then, if those two values agree, we’ll be accepting the button press, 
// otherwise we won’t. 
// Also, we have to consider that not all switches have the same transient 
// responses and periods. 
// So, remember that in your own projects, you’ll have to adjust for that fact 
// (do some tryouts and figure out what is the bulk transient period of your own 
// switches).


// Connect the push button to pin 2
const int PB_PIN = 2;

// Uses the onboard LED on pin 13
const int LED_PIN = 13;

// Duration of the transient period, in milliseconds
// Note: Giving a larger value won't hurt
const int TRANSIENT_PERIOD = 10;

// Flag to indicate the start of the transient period
boolean transientPeriodStarted = false;

// Flag to indicate the state of the LED
boolean ledOn = false;

// Flag to indicate if we have already accepted the
// button press and we've handled the event
boolean bPressAccepted = false;

// Represents a (reference) point in time
unsigned long timeRef = 0;

void setup()
{
    pinMode(PB_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (digitalRead(PB_PIN) == LOW)
  {
    // If transient response has just started
    if (!transientPeriodStarted)
    {
      // Sets the flag for the start of the transient period
      transientPeriodStarted = true;
      
      // Updates the time reference
      timeRef = millis();
    }
    // If the transient period has passed 
    // and we haven't already accepted the button press 
    else if (!bPressAccepted && (unsigned long)(millis() - timeRef) > TRANSIENT_PERIOD)
    {
      // Toggles the state of the LED
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn); 
      
      // Updates the flag for the acceptance of the button press 
      bPressAccepted = true;
    }
  }
  // The button has been released
  else
  {
    // Resets the flags
    transientPeriodStarted = false;
    bPressAccepted = false;
  }
}

