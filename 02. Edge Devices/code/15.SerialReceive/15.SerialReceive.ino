const int ledPin = 13; // pin the LED is connected to
int   blinkRate = 100; // blink rate stored in this variable

// blink the LED with the on and off times determined by blinkRate
void blink() {
  digitalWrite(ledPin,HIGH);
  // delay depends on blinkrate value
  delay(blinkRate); 
  digitalWrite(ledPin,LOW);
  delay(blinkRate);
}

void setup() {
  Serial.begin(9600);      // initialize serial port to send and receive at 9600 baud
  pinMode(ledPin, OUTPUT); // set this pin as output
}

/*
void loop() {
  // check to see if at least one character is available
  if ( Serial.available()) {
    char ch = Serial.read();

    // is this an ascii digit between 0 and 9?
    if(ch >= '0' && ch <= '9') {
       // ASCII value converted to numeric value
       blinkRate = (ch - '0');  

       // actual blinkrate is 100 mS times received digit    
       blinkRate = blinkRate * 100; 
    }
  }
  blink();
}
*/


int   value;

void loop()
{
  if ( Serial.available() ) 
  {
    char ch = Serial.read();
    
    if(ch >= '0' && ch <= '9') {
       // Each digit is converted from its ASCII value to its numeric value. 
       // Because the numbers are decimal numbers, each successive number is multiplied by 10
       value = (value * 10) + (ch - '0');      
    }

    // Gets digits until the newline character is received.
    // The newline character (ASCII value 10) can be appended automatically each time you click "Send"   
    // change the option from “No line ending” to “Newline” in the Serial Monitor
    else if (ch == 10) {
       blinkRate = value * 100;
       Serial.println(blinkRate);
       value = 0;
    }
  }
  blink();
}

