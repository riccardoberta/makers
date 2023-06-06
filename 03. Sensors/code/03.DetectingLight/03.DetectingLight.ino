// Connect the I2C pins (SCL and SDA) to Arduino.
// The pins are different on different Arduinos:
// SDA (A4)
// SCL(A5)

#include <SparkFunTSL2561.h>
#include <Wire.h>

// Create an SFE_TSL2561 object, here called "light":
SFE_TSL2561 light;

// Global variables
boolean gain;     // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;  // Integration ("shutter") time in milliseconds

void setup() {
  Serial.begin(9600);
  
  // Initialize the SFE_TSL2561 library

  // You can pass nothing to light.begin() for the default I2C address (0x39),
  // or use one of the following presets if you have changed the ADDR jumper on the board:
  light.begin();

  // Get factory ID from sensor:
  // (Just for fun, you don't need to do this to operate the sensor)
  unsigned char ID;
  if (light.getID(ID)) {
    Serial.print("Got factory ID: 0X");
    Serial.print(ID,HEX);
    Serial.println(", should be 0X5X");
  }

  // Most library commands will return true if communications was successful,
  // and false if there was a problem. We can ignore this returned value,
  // or check whether a command worked correctly and retrieve an error code:
  else {
    byte error = light.getError();
    printError(error);
  }

  // The light sensor has a default integration time of 402ms,
  // and a default gain of low (1X).
  
  // If gain = false (0), device is set to low gain (1X)
  // If gain = high (1), device is set to high gain (16X)
  gain = 0;

  // If time = 0, integration will be 13.7ms
  // If time = 1, integration will be 101ms
  // If time = 2, integration will be 402ms
  // If time = 3, use manual start / stop to perform your own integration
  unsigned char time = 2;

  // setTiming() will set the third parameter (ms) to the
  // requested integration time in ms (this will be useful later):
  Serial.println("Set timing...");
  light.setTiming(gain,time,ms);

  // To start taking measurements, power up the sensor:
  Serial.println("Powerup...");
  light.setPowerUp();
  
  // The sensor will now gather light during the integration time.
  // After the specified time, we can retrieve the result from the sensor.
  // Once a measurement occurs, another integration period will start.
}

void loop() {
  // Wait between measurements before retrieving the result
  // We can also configure the sensor to issue an interrupt
  // when measurements are complete
  
  // This sketch uses the TSL2561's built-in integration timer.
  // We can also perform our own manual integration timing
  // by setting "time" to 3 (manual) in setTiming(),
  // then performing a manualStart() and a manualStop() as in the below
  // commented statements:
  // ms = 1000;
  // light.manualStart();
  // delay(ms);
  // light.manualStop();
  
  // Once integration is complete, we'll retrieve the data.
  // There are two light sensors on the device, one for visible light
  // and one for infrared. 
  // Both sensors are needed for lux calculations.
  unsigned int data0, data1;
  
  if (light.getData(data0,data1)) {
    Serial.print("data0: ");
    Serial.print(data0);
    Serial.print(" data1: ");
    Serial.print(data1);
  
    // To calculate lux, pass all our settings and readings
    // to the getLux() function.
    
    // The getLux() function will return 1 if the calculation
    // was successful, or 0 if one or both of the sensors was
    // saturated (too much light). If this happens, we can
    // reduce the integration time and/or gain.
  
    double lux;
    boolean good = light.getLux(gain,ms,data0,data1,lux);

    Serial.print(" lux: ");
    Serial.print(lux);
    if (good) Serial.println(" (good)"); 
    else Serial.println(" (BAD)");
  }
  else
  {
    byte error = light.getError();
    printError(error);
  }
}

void printError(byte error) {
  Serial.print("I2C error: ");
  Serial.print(error,DEC);
  Serial.print(", ");
  
  switch(error) {
    case 0:
      Serial.println("success");
      break;
    case 1:
      Serial.println("data too long for transmit buffer");
      break;
    case 2:
      Serial.println("received NACK on address (disconnected?)");
      break;
    case 3:
      Serial.println("received NACK on data");
      break;
    case 4:
      Serial.println("other error");
      break;
    default:
      Serial.println("unknown error");
  }
}
