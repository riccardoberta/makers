// Pin Definitions
const int PulseSensorPin = A0; 
const int LEDPin = LED_BUILTIN;

// Variables to store the sensor data and threshold
// to detect a heartbeat (adjust based on your setup)
int Signal = 0;             
const int Threshold = 580; 

void setup() {
  pinMode(LEDPin, OUTPUT);    
  Serial.begin(115200);      
}

void loop() {
  // Read the raw signal from the Pulse Sensor
  Signal = analogRead(PulseSensorPin);

  // Print the signal value to the Serial Plotter for visualization
  Serial.println("Signal: " + String(Signal));

  // Check if the signal is above the threshold
  if (Signal > Threshold) {
    digitalWrite(LEDPin, HIGH); // Turn on the LED if a heartbeat is detected
  } else {
    digitalWrite(LEDPin, LOW);  // Turn off the LED otherwise
  }

  // Add a small delay to stabilize readings (20ms = 50Hz sampling rate)
  delay(20);
}