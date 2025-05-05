// Function

// A function to calculates the average of a number of readings
// from a sensor connected to a specific pin
float average_reading(int sensor_pin, int size) {
    int i;
    float average;
    float sum;

    // Initialize the sum to zero
    sum = 0.0;
    
    // Read the sensor value 'size' times and add them to the sum
    for (i=1; i<=size; i++) {
        sum = sum + analogRead(sensor_pin);
    }

    // Calculate the average by dividing the sum by the 
    // number of readings  
    average = sum/size;
  
    // Return the average
    return(average);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
    // Numer of readings
    int n=15;

    // Pin to which the potentiometer is connected
    int pot_pin=1;

    // The reading from the potentiometer
    float reading;

    // Call the average_reading function to calculate the average reading
    reading = average_reading(pot_pin,n);

    // Print the reading and voltage to the serial monitor
    Serial.println(reading);
    Serial.println();
}