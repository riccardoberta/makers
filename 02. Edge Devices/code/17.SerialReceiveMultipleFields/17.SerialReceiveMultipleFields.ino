// This code expects a message in the format: 12,345,678

const int NUMBER_OF_FIELDS = 3; // how many comma separated fields we expect
int fieldIndex = 0;             // the current field being received
int values[NUMBER_OF_FIELDS];   // array holding values for all the fields

void setup()
{
  // Initialize serial port to send and receive at 9600 baud
  Serial.begin(9600); 
}

// The code receives a message with three numeric fields separated by commas
// It uses the technique described for receiving digits, and it adds code to identify 
// comma-separated fields and store the values into an array

void loop()
{
  if( Serial.available())
  {
    char ch = Serial.read();
    
    // is this an ascii digit between 0 and 9?
    if(ch >= '0' && ch <= '9') {
      // yes, accumulate the value
      values[fieldIndex] = (values[fieldIndex] * 10) + (ch - '0'); 
    }
    
    // comma is our separator, so move on to the next field
    else if (ch == ',') {
      if(fieldIndex < NUMBER_OF_FIELDS-1)
        fieldIndex++;  
    }

    // any character not a digit or comma ends the acquisition of fields
    // in this example it's the newline character sent by the Serial Monitor  
    else {
      Serial.print( fieldIndex +1);
      Serial.println(" fields received:");
      for(int i=0; i <= fieldIndex; i++) {
        Serial.println(values[i]);

        // set the values to zero, ready for the next message
        values[i] = 0; 
      }

      // ready to start over
      fieldIndex = 0;  
    }
  }
}
      
    

