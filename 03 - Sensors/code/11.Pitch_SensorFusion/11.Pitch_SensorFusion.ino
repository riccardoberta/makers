// Include the sensor library and the I2C library
#include <Wire.h>
#include "ICM_20948.h"

// Create an ICM_20948 object
ICM_20948_I2C myICM;

// Complementary filter parameter
const float alpha = 0.8;  

// Estimated pitch angle (initialized to 90)
float pitch_acc = 90;
float pitch_gyro = 90;
float pitch = 90;         

// Timer variables for delta time calculation
unsigned long timer = 0;

void setup() {
  Serial.begin(115200);   
  Wire.begin();          
  
  // Initialize the ICM-20948
  if (myICM.begin(Wire, 0x68) != ICM_20948_Stat_Ok) {
    Serial.println("IMU initialization failed!");
    while (1);
  }
  Serial.println("IMU initialized successfully!");

  // Initialize time tracking
  timer = millis(); 
}

void loop() {
  // If sensor data is available
  if (myICM.dataReady()) {
    
    // Read accelerometer, gyroscope, and magnetometer data
    myICM.getAGMT(); 

    // Extract accelerometer data
    float ax = myICM.accX();
    float ay = myICM.accY();
    float az = myICM.accZ();

    // Compute pitch angle from the accelerometer
    pitch_acc = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

    // Extract gyroscope data
    float vy = myICM.gyrY();

    // Compute time difference (Δt) in seconds
    float dt = (double)(millis() - timer) / 1000.0;  

    // Compute pitch angle from the gyroscope
    pitch_gyro += vy * dt;
    
    // Compute pitch using the complementary filter
    pitch = alpha * (pitch + vy * dt) + (1 - alpha) * pitch_acc;

    // Update previous time
    timer = millis();

    // Print pitch angle to Serial Monitor
    Serial.print("Pitch: ");
    Serial.print(pitch_acc);
    Serial.print(":");
    Serial.print(pitch_gyro);
    Serial.print(":");
    Serial.println(pitch);
  } 

  // Small delay to make output readable
  delay(10);  // Reduced delay for smoother angle tracking
}
