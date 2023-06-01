// Integers
// Demonstrate truncation with integer arithmetic

void setup() 
{
  int i,j;
  
  Serial.begin(9600);
  
  //  wait for user to open the serial monitor
  delay(3500);           
  
  i = (2/3)*4;
  j = i + 2;
  Serial.println("First test"); 
  Serial.print(i);  
  Serial.print("  ");   
  Serial.println(j);

  i = (2.0/3.0)*4.0;
  j = i + 2;
  Serial.println("Second test"); 
  Serial.print(i);  
  Serial.print("  ");   
  Serial.println(j);  
}

// Loop does nothing.  Code in setup() is executed only once
void loop() 
{

}     
