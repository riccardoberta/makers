// Include the sensor library and the I2C library
#include <Wire.h>
#include "ICM_20948.h"

// Create an ICM_20948 object
ICM_20948_I2C myICM;

// Variable to store the timer for pitch calculation 
// usgin integration of gyroscope data
unsigned long timer;

// Variable to store the pitch angle
// initialized to 90 degrees (the first position)
float pitch = 90; 

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

    // Extract gyroscope data
    float vx = myICM.gyrX();
    float vy = myICM.gyrY();
    float vz = myICM.gyrZ();

    // Calculate the pitch angle based on gyroscope Y-axis data
    // This is an integration of the velocity over time to get the angle
    float dt = (double)(millis() - timer) / 1000.0; 
    pitch += vy * dt;

    // Update the timer for the next calculation
    timer = millis();

    // Send pitch angle to Serial Monitor
    Serial.print("Pitch: ");
    Serial.println(pitch);
  } 

  // Small delay to make output readable
  delay(200); 
}