// Include the Wire library for I2C communication
#include <Wire.h>

// Define the Nunchuk  slave address
#define NUNCHUK_ADDRESS 0x52

// Buffer for data received
static uint8_t nunchuck_buf[6];

// Establishes I2C communication with the nunchuck
static void nunchuck_init() { 
    // Join the I2C bus a s master
    Wire.begin();   

    // Initialize the slave device (nunchuck) on address 0x52
    Wire.beginTransmission(NUNCHUK_ADDRESS);

    // Send handshake signal to initialize the Nunchuk
    Wire.write((uint8_t)0x40);
    Wire.write((uint8_t)0x00);
    delay(100);
    Wire.endTransmission();

    Serial.println("Wii Nunchuk initialized!");
}

static void nunchuck_send_request() {
    Wire.beginTransmission(NUNCHUK_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
}

// A function to decode Nunchuk data
char nunchuk_decode(char reading) {
  return (reading ^ 0x17) + 0x17;
}

// Receive data from the nunchuck
static int nunchuck_get_data() {
    int cnt=0;

    // Get six bytes of data from device 0x52 (nunchuck).
    Wire.requestFrom (NUNCHUK_ADDRESS, 6);

    // Indicate how many bytes have been received
    while (Wire.available ()) {
      nunchuck_buf[cnt] = nunchuk_decode( Wire.read() );
      cnt++;
    }

    nunchuck_send_request();
    
    if (cnt >= 5) {
        return 1; 
    }
    
    return 0;
}

int nunchuck_zbutton() { return ((nunchuck_buf[5] >> 0) & 1) ? 0 : 1; }
int nunchuck_cbutton() { return ((nunchuck_buf[5] >> 1) & 1) ? 0 : 1;  }
int nunchuck_joyx() { return nunchuck_buf[0]; }
int nunchuck_joyy() { return nunchuck_buf[1]; }
int nunchuck_accelx() { return nunchuck_buf[2]; }
int nunchuck_accely() { return nunchuck_buf[3]; }
int nunchuck_accelz() { return nunchuck_buf[4]; }

void setup() {
    Serial.begin(9600);
    nunchuck_init();
}

void loop() {
  
  nunchuck_get_data();

  Serial.write(nunchuck_joyy());
    
  delay(100);  
}