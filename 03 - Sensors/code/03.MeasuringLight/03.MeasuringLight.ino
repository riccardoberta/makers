// Include the TSL2561 sensor library
#include <SparkFunTSL2561.h>  

// Include the I2C library for communication
#include <Wire.h>  

// Create an SFE_TSL2561 object to represent the light sensor
SFE_TSL2561 light;

// Global variables to store settings
// Gain setting: 0 = X1 (low gain), 1 = X16 (high gain)
// Integration ("shutter") time in milliseconds
boolean gain;     
unsigned int ms;  

void setup() {
  Serial.begin(9600);
  
    // Initialize the TSL2561 sensor. 
    // If no I2C address is provided, it uses the default (0x39).
    if (!light.begin()) {
        Serial.println("Error: Sensor initialization failed!");
        while (1);
    }

    // Configure gain
    // gain = 0, device is set to low gain (1X)
    // gain = 1, device is set to high gain (16X)
    gain = 0;

    // Configure integration time
    // intgration_time = 0, integration will be 13.7ms (short integration time)
    // intgration_time = 1, integration will be 101ms (medium integration time)
    // intgration_time = 2, integration will be 402ms (long integration time)
    // intgration_time = 3, use manual start / stop to perform your own integration
    int intgration_time = 2;

    // Set the gain and integration time, the library will provide
    // the timing for the integration time in ms
    light.setTiming(gain, intgration_time, ms);

    // Power up the sensor to begin measurements
    Serial.println("Powering up the sensor...");
    light.setPowerUp();
}

void loop() {
  
  // Read the light sensor data (visible and infrared readings)
  unsigned int data0, data1;
  if (light.getData(data0, data1)) {
    
    // Print raw sensor data
    Serial.print("Data0 (Visible Light): ");
    Serial.print(data0);
    Serial.print("  Data1 (Infrared Light): ");
    Serial.println(data1);
  
    // Calculate the lux (light intensity) based on the sensor readings
    double lux;
    boolean good = light.getLux(gain, ms, data0, data1, lux);

    // Print the lux value and indicate if the calculation was successful
    Serial.print("Lux: ");
    Serial.print(lux);
    if (good)
      Serial.println(" (Good measurement)");
    else
      Serial.println(" (Bad measurement: Sensor may be saturated)");

  } 

  // If data retrieval fails, print the error
  else {
    byte error = light.getError();
    switch (error) {
        case 0:
            Serial.println("Success");
            break;
        case 1:
            Serial.println("Data too long for transmit buffer");
            break;
        case 2:
            Serial.println("Received NACK on address (disconnected?)");
            break;
        case 3:
            Serial.println("Received NACK on data");
            break;
        case 4:
            Serial.println("Other error");
            break;
        default:
            Serial.println("Unknown error");
    }
  }

  // Delay before the next measurement cycle
  delay(1000);
}