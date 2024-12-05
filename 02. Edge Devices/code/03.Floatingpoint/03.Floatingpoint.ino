// Floatingpoint 
// Demonstrate well-known round-off error problem with 
// floating point arithmetic

void setup() 
{
  float w,x,y,z;
  
  Serial.begin(9600);
  delay(2500);           
  
  w = 4.0/3.0;
  x = w - 1;
  y = 3*x;
  z = 1 - y;

  Serial.println("\nFloating point arithmetic test"); 

// Use two-parameter form of Serial.print.  
// The second parameter specifies
// the number of digits in value sent to the Serial Monitor
  Serial.println(w,16);  
  Serial.println(x,8);  
  Serial.println(y,8);  
  Serial.println(z,8);  

  Serial.println(z*1.0e7,8);  
}

void loop() {}     
