
// Define the pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Define variables for the duration and distance
float duration, distance;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    // Send a 10 µs pulse to the trigger pin  
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the duration of the echo pulse
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance based on the speed of sound
    distance = (duration*.0343)/2;
    
    // Print the distance to the serial monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    
    // Delay before the next measurement
    delay(100);
}