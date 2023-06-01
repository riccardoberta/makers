#define HEADER '|'
#define MOUSE 'M'
#define MESSAGE_BYTES 5 // the total bytes in a message

void setup() {
   Serial.begin(9600);
}

void loop() {
   // check to ensure that we don’t try to process the message 
   // until all the required data is available
   if ( Serial.available() >= MESSAGE_BYTES) {
      
      // only read the rest of the message if 
      // a valid header has been received
      if( Serial.read() == HEADER) {
         char tag = Serial.read();
         if(tag == MOUSE) {

            // Convert the two bytes back to an integer
            int index = Serial.read(); 
            int val = Serial.read() * 256;
            val = val + Serial.read();

            Serial.print("Received mouse msg, index = ");
            Serial.print(index);
            Serial.print(", value ");
            Serial.println(val);
        }

        // if the code gets here, the tag was not recognized. 
        // this helps to ignore data that may be incomplete or corrupted.
        else {
            Serial.print("got message with unknown tag ");
            Serial.println(tag);
        }
      } 
   } 
}

