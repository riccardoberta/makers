#include <Wire.h>

// Define the I2C address of the TMP102 senso
int tmp102Address = 0x48;


// A faunction to read the temperature from the TMP102 sensor
float getTemperature() {

    // Request 2 bytes of data 
    Wire.requestFrom(tmp102Address, 2);

    // Read the most significant and the least significant bytes
    byte MSB = Wire.read();
    byte LSB = Wire.read();

    // Combine the two bytes into a 12-bit integer
    // The temperature is a 12-bit value, using two's complement 
    // for negative values
    int TemperatureSum = ((MSB << 8) | LSB) >> 4; 
    float celsius = TemperatureSum * 0.0625;
    
    // Return the temperature in Celsius
    return celsius;
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void loop() {

    // Get the temperature in Celsius
    float celsius = getTemperature();

    // Print the temperature to the serial monitor
    Serial.print("Celsius: ");
    Serial.println(celsius);

    // Delay to slow down the output
    delay(200); 
}