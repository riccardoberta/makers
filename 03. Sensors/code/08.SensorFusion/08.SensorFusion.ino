#include <Wire.h>
#include <SPI.h>
#include "SparkFunLSM9DS1.h"
#include "Kalman.h"

#define LSM9DS1_M	0x1E 
#define LSM9DS1_AG	0x6B
#define DECLINATION 2.12 

LSM9DS1 imu;

Kalman kalmanRoll;
Kalman kalmanPitch;

float accroll = 0;
float accpitch = 0;
float gyropitch = 0;
float gyroroll = 0;
float pitch = 0;
float roll = 0;

unsigned long timer;

void setup() {
  Serial.begin(115200);
  
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  
  if (!imu.begin()) {
    Serial.println("Failed to communicate with LSM9DS1.");
    while (1);
  }

  imu.calibrate();
  timer = millis();
}

void loop() {
  imu.readAccel();
  imu.readGyro();
  
  sendPitchRoll(imu.calcAccel(imu.ax), 
                imu.calcAccel(imu.ay), 
                imu.calcAccel(imu.az), 
                imu.calcGyro(imu.gx), 
                imu.calcGyro(imu.gy), 
                imu.calcGyro(imu.gz));
  delay(10);
}

void sendPitchRoll(float ax, float ay, float az, float gx, float gy, float gz) {
  
  // Accelerometer
  accroll = atan2(-ay, az) * 180.0/PI;
  accpitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0/PI;

  // Gyro
  gyropitch += gy * (double)(millis() - timer) / 1000;
  gyroroll  += gx * (double)(millis() - timer) / 1000;

  // Kalman
  pitch = kalmanPitch.filter(accpitch, gy, (double)(millis() - timer)/1000);
  roll = kalmanRoll.filter(accroll, gx, (double)(millis() - timer)/1000);

  Serial.print(accpitch);
  Serial.print(":");
  Serial.print(accroll);
  Serial.print(":");
  Serial.print(gyropitch);
  Serial.print(":");
  Serial.print(gyroroll);
  Serial.print(":");
  Serial.print(pitch);
  Serial.print(":");
  Serial.print(roll);
  Serial.println(":");

  timer = millis();
}
