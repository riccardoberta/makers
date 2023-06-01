#include <Arduino.h>

// Port registers allow for lower-level and faster manipulation of the i/o pins. 
// Three ports: B (digital 8 to 13); C (analog); D (digital0 to 7)
// Each port is controlled by three registers. 
// The DDR register determines whether the pin is an INPUT or OUTPUT. 
// The PORT register controls whether the pin is HIGH or LOW, and the PIN register reads the state of pins 
// Ex: DDRD = B11111110;  // sets Arduino pins 1 to 7 as outputs, pin 0 as input
#define pwrpin PORTC3
#define gndpin PORTC2

static uint8_t nunchuck_buf[6];

static void nunchuck_setpowerpins() {
    // _BV() is a macro defined as #define _BV(bit) ( 1<<(bit) ) 
    // It stands for Bit Value where you pass it a bit and it gives 
    // you the byte value with that bit set. 
    // Ex: PORTC &= ~(_BV(1));  clear bit 1 only

    DDRC |= _BV(pwrpin) | _BV(gndpin);

    // Provide power through analog pins 2 and 3
    PORTC &=~ _BV(gndpin);
    PORTC |=  _BV(pwrpin);
    delay(100);          
}

// Establishes I2C communication with the nunchuck

static void nunchuck_init() { 
    // Join the I2C bus a s master
    Wire.begin();   

    // Initialize the slave device (nunchuck) on address 0x52
    Wire.beginTransmission(0x52);

    // Wire.write() puts the given values into a buffer within the Wire 
    // library where data is stored until Wire.endTransmission is called 
    // to actually do the sending
    Wire.write((uint8_t)0x40);
    Wire.write((uint8_t)0x00);
    delay(100);
    Wire.endTransmission();
 }

static void nunchuck_send_request() {
    Wire.beginTransmission(0x52);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
}

// Decoding is required to convert the values sent into numbers
static char nunchuk_decode_byte (char x) {
    x = (x ^ 0x17) + 0x17;
    return x;
}

// Receive data from the nunchuck
static int nunchuck_get_data() {
    int cnt=0;

    // Get six bytes of data from device 0x52 (nunchuck).
    Wire.requestFrom (0x52, 6);

    // Indicate how many bytes have been received
    while (Wire.available ()) {
      nunchuck_buf[cnt] = nunchuk_decode_byte( Wire.read() );
      cnt++;
    }
    nunchuck_send_request();
    if (cnt >= 5) {
        return 1; 
    }
    return 0;
}

static int nunchuck_zbutton() { return ((nunchuck_buf[5] >> 0) & 1) ? 0 : 1; }
static int nunchuck_cbutton() { return ((nunchuck_buf[5] >> 1) & 1) ? 0 : 1;  }
static int nunchuck_joyx() { return nunchuck_buf[0]; }
static int nunchuck_joyy() { return nunchuck_buf[1]; }
static int nunchuck_accelx() { return nunchuck_buf[2]; }
static int nunchuck_accely() { return nunchuck_buf[3]; }
static int nunchuck_accelz() { return nunchuck_buf[4]; }
