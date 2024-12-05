// Repetion

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{  
  int i;
  for (i=0; i<10; i++) {
    Serial.println(i);
    delay(100);
  }
  
  Serial.println("for loop over\n");
}
