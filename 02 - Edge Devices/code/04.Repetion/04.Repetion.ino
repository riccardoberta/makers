// Repetion

void setup() {
  Serial.begin(9600);
}

void loop() {
    // define the variables
    int i;

    // Print the numbers from 0 to 9 using a for loop
    for (i=0; i<10; i++) {
        Serial.println(i);
        delay(100);
    }
  
     Serial.println("for loop over\n");
}
