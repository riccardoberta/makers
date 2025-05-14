// The pin to which the LED is connected
const int led_pin = 13; 

// Initial blink rate 
int blink_rate = 100; 

// Function to controls the LED by turning it on, waiting for the blink_rate duration, 
// then turning it off for the same duration.
void blink() {
  digitalWrite(led_pin, HIGH);
  delay(blink_rate); 
  digitalWrite(led_pin, LOW);
  delay(blink_rate);
}

void setup() {
  Serial.begin(9600); 
  pinMode(led_pin, OUTPUT);
}

/*
void loop() {
  // Check to see if at least one character is available
  if (Serial.available()) {

    // If data is available, reads a character
    char ch = Serial.read();

    // If the character is a numeric ASCII digit ('0' to '9'), 
    // convert it to its numeric equivalent using (ch - '0')
    if(ch >= '0' && ch <= '9') {
       blink_rate = (ch - '0');  
       blink_rate = blink_rate * 100; 
    }
  }

  // Call the blink function to blink the LED
  blink();
}
*/

// Variable to accumulate the digits of the number
int value;

void loop() {
    if (Serial.available()) {
        char ch = Serial.read();
    
        // The accumulated number is updated as a decimal value by multiplying the 
        // existing value by 10 and adding the new digit
        if(ch >= '0' && ch <= '9') {
            value = (value * 10) + (ch - '0');      
        }

        // When a newline character is received, the accumulated value is used to 
        // calculate the new blinkRate. The value variable is reset to 0 
        // to prepare for the next input.
        else if (ch == 10) {
            blink_rate = value * 100;
            Serial.println(blink_rate);
            value = 0;
        }
    }
    blink();
}

