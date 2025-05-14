// select the input pin for the photoresistos
const int pin = 0;    

// variable to store the value coming from the sensor
int val = 0;             

void setup() {
  Serial.begin(9600);
}

void loop()  {
  // read the voltage on the photoresistor
  val = analogRead(pin);   

  // print the value to the serial port
  Serial.println(val);
}
