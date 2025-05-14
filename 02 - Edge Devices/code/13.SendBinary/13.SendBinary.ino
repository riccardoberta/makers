// Declare a 16-bit integer variable
int value; 

void setup() {
    Serial.begin(9600);
}

void loop() {
    // send a header character    
    Serial.print('H'); 

    // Generate a random integer
    value = random(599);

    // Send the low and high bytes 
    Serial.write(lowByte(value));  
    Serial.write(highByte(value));

    delay(1000);
}
      
    

