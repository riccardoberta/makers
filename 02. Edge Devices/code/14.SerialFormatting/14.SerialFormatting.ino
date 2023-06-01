char chrValue = 65;  // these are the starting values to print
int intValue  = 65;
float floatValue = 65.0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("chrValue: ");
  Serial.println(chrValue);
  Serial.println(chrValue,DEC);

  Serial.println("intValue: ");
  Serial.println(intValue);
  Serial.println(intValue,DEC);
  Serial.println(intValue,HEX);
  Serial.println(intValue,OCT);
  Serial.println(intValue,BIN);

  Serial.println("floatValue: ");
  Serial.println(floatValue);

  delay(3000); // delay a second between numbers
  chrValue++;  // to the next value
  intValue++;
}
      
    

