void setup() {
  int i,j;
  
  // initialize serial communication
  Serial.begin(9600);
  
  //  wait for user to open the serial monitor
  delay(3500);           
  
  // 2/3 is performed using integer division, which results in 0 
  // because 2 and 3 are both integers and the result of their division is truncated 
  // (i.e., the fractional part is discarded). 
  // This result is then multiplied by 4, which gives i = 0. 
  i = (2/3)*4;
  
  // The variable j is then assigned the value of i + 2, which results in j = 2.
  j = i + 2;

  // Print the values of i and j to the serial monitor
  Serial.println("First test"); 
  Serial.print(i);  
  Serial.print("  ");   
  Serial.println(j);

  // In this case, 2.0 and 3.0 are floating-point numbers, so the division result 
  // is a floating-point number, yielding approximately 0.6667
  // This value is then multiplied by 4.0, resulting in i = 2.6667
  // However, because i is declared as an int, it will be truncated when stored, so i = 2
  i = (2.0/3.0)*4.0;
  
  // The variable j is then assigned the value of i + 2, which gives j = 4 
  j = i + 2;
  
  Serial.println("Second test"); 
  Serial.print(i);  
  Serial.print("  ");   
  Serial.println(j);  
}

// Loop does nothing. 
void loop() { }     
