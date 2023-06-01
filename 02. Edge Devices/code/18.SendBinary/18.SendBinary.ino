int intValue;    // an integer value (16 bits)

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print('H'); // send a header character

  // send a random integer
  intValue = random(599);

  // To send an integer from Arduino we need to send the low and high bytes 
  //that make up the integer
  Serial.write(lowByte(intValue));  // send the low byte
  Serial.write(highByte(intValue)); // send the high byte

  // send another random integer
  intValue = random(599); // generate a random number between 0 and 599
  
  // send the two bytes that comprise an integer
  Serial.write(lowByte(intValue));  // send the low byte
  Serial.write(highByte(intValue)); // send the high byte

  delay(1000);
}
      
    

