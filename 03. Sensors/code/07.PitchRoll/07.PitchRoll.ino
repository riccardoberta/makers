#include <Wire.h>
#include <SPI.h>
#include "SparkFunLSM9DS1.h"

LSM9DS1 imu;

#define LSM9DS1_M	0x1E 
#define LSM9DS1_AG	0x6B
#define DECLINATION 2.12 

unsigned long timer;

float roll_acc = 0;
float pitch_acc = 0;

float roll_gyro = 0;
float pitch_gyro = 0;
  
void setup()  {
  Serial.begin(115200);
  
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  
  if (!imu.begin()) {
    Serial.println("Failed to communicate with LSM9DS1.");
    while (1);
  }

  imu.calibrate();
}

void loop() {
  //imu.readAccel();
  imu.readGyro();

  // Accelerometer
  //sendPitchRoll_acc(imu.calcAccel(imu.ax), imu.calcAccel(imu.ay), imu.calcAccel(imu.az));
  
  // Gyroscope
  sendPitchRoll_gyro(imu.calcGyro(imu.gx), imu.calcGyro(imu.gy));
  
  delay(25);
}

void sendPitchRoll_acc(float ax, float ay, float az) {
  pitch_acc = atan2(-ax, sqrt(ay * ay + az * az))  * 180.0/PI;
  roll_acc = atan2(-ay, az) * 180.0/PI;
  Serial.print(pitch_acc);
  Serial.print(":");
  Serial.println(roll_acc);
}

void sendPitchRoll_gyro(float gx, float gy) {
  pitch_gyro += gy * (double)(millis() - timer) / 1000;
  roll_gyro  += gx * (double)(millis() - timer) / 1000;
  Serial.print(pitch_gyro);
  Serial.print(":");
  Serial.println(roll_gyro);
  timer = millis();
}
