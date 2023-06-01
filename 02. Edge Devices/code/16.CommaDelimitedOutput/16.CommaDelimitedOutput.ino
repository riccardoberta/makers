void setup() {
  Serial.begin(9600);
}

void loop() {
  // some hardcoded values to send
  int value1 = 10;    
  int value2 = 100;
  int value3 = 1000;

  // A unique header to identify start of message.
  // We have to ensure that the receiving side can determine the start 
  // of a message to make sure it has all the data for all the fields.
  // The header character must be unique; it should not appear within 
  // any of the data fields and it must also be different from the separator
  // character
  Serial.print('H'); 

  // Send a text string with all the fields separated by a delimiting (separating) 
  // character, such as a comma
  // We have to choose a separating character that will never occur within actual data; 
  // if our data consists only of numeric values, a comma is a good choice for a delimiter.
  Serial.print(",");

  Serial.print(value1,DEC);
  Serial.print(",");
  
  Serial.print(value2,DEC);
  Serial.print(",");
  
  Serial.print(value3,DEC);
  Serial.print(",");  
  
  // This is used to help the receiving side know that the full message string 
  // has been received
  Serial.println();  // send a cr/lf
  delay(100);
}

