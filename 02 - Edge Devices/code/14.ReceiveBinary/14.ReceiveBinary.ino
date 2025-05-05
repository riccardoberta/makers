// Define header, tag, and message length
#define HEADER '|'
#define MOUSE 'M'
#define MESSAGE_BYTES 5 

void setup() {
   Serial.begin(9600);
}

void loop() {
    // Check if there are enough bytes available to read
    if ( Serial.available() >= MESSAGE_BYTES) {
      
      // Check the header byte
      if( Serial.read() == HEADER) {

        // Read the tag byte
        char tag = Serial.read();
         
        // Check if the tag is for a mouse message
        if(tag == MOUSE) {

            // Read the X-coordinate (1 byte) 
            int x = Serial.read(); 

            // Read the Y-coordinate (2 byte) and reconstruct the value
            int y = Serial.read() * 256;
            y = y + Serial.read();

            // Send back the received values
            Serial.print("Received mouse msg, x = ");
            Serial.print(x);
            Serial.print(", y ");
            Serial.println(y);
        }

        // If the code gets here, the tag was not recognized. 
        // this helps to ignore data that may be incomplete or corrupted.
        else {
            Serial.print("got message with unknown tag ");
            Serial.println(tag);
        }
      } 
   } 
}