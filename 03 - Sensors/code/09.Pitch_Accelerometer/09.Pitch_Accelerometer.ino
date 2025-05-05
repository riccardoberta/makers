// Include the sensor library and the I2C library
#include <Wire.h>
#include "ICM_20948.h"

// Create an ICM_20948 object
ICM_20948_I2C myICM;

void setup() {
  Serial.begin(115200);   
  Wire.begin();          
  
  // Initialize the ICM-20948
  if (myICM.begin(Wire, 0x68) != ICM_20948_Stat_Ok) {
    Serial.println("IMU initialization failed!");
    while (1);
  }
  Serial.println("IMU initialized successfully!");
}

void loop() {
  
  // If sensor data ready are available
  if (myICM.dataReady()) {
    
    // Read accelerometer, gyroscope, and magnetometer data
    myICM.getAGMT(); 

    // Extract accelerometer data
    float ax = myICM.accX();
    float ay = myICM.accY();
    float az = myICM.accZ();

    // Calculate pitch angle (in degrees)
    float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

    // Send pitch angle to Serial Monitor
    Serial.print("Pitch: ");
    Serial.println(pitch);
  } 

  // Small delay to make output readable
  delay(200); 
}