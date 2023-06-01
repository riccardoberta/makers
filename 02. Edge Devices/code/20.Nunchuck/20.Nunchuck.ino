// The I2C library that is included with the Arduino release
#include <Wire.h> 

// A library to hide the I2C interface
#include "nunchuck.h"

byte accx;

void setup()
{
  Serial.begin(9600);
  nunchuck_setpowerpins();
  nunchuck_init();
}

void loop()
{
  nunchuck_get_data();
  
  // To get the value of acceleration in the x-axis from the nunchuck and store it
  accx  = nunchuck_accelx();

  Serial.print(nunchuck_buf[0]);
  Serial.print(" ");
  Serial.print(nunchuck_buf[1]);
  Serial.print(" ");
  Serial.print(nunchuck_buf[2]);
  Serial.print(" ");
  Serial.print(nunchuck_buf[3]);
  Serial.print(" ");
  Serial.print(nunchuck_buf[4]);
  Serial.print(" ");
  Serial.print(nunchuck_buf[5]);
  Serial.println(" ");


  if( accx >= 75 && accx <= 185) {
    // map returns a value from 0 to 63 for values from 75 to 185
    byte  y = map(accx, 75, 185, 0, 63);
    Serial.write(y);
  }
  
  delay(500); 
}
      
    

