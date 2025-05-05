// Analog pin connected to the sensor
const int SENSOR_PIN = A0;  

// Reference voltage in millivolts (5V for most Arduino boards)
const long REFERENCE_MV = 5000;  

// Distance table configuration
const int TABLE_ENTRIES = 12;  // Number of entries in the distance table
const int INTERVAL = 250;      // Millivolts separating each table entry

// Distance in cm corresponding to each 250 mV interval
static int distanceTable[TABLE_ENTRIES] = {150, 140, 130, 100, 60, 50, 40, 35, 30, 25, 20, 15};

// Function to calculate the distance based on the sensor's output voltage
int getDistance(int millivolts) {
    // If the millivolts exceed the last table entry, return the last value
    if (millivolts >= INTERVAL * TABLE_ENTRIES) {
        return distanceTable[TABLE_ENTRIES - 1];
    }

    // Calculate the index of the table entry
    int index = millivolts / INTERVAL;

    // Calculate the fractional part for interpolation
    float fraction = (millivolts % INTERVAL) / (float)INTERVAL;

    // Perform linear interpolation between the current and next table entries
    return distanceTable[index] - ((distanceTable[index] - distanceTable[index + 1]) * fraction);
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Read the analog value from the sensor
    int sensorValue = analogRead(SENSOR_PIN);

    // Convert the analog value to millivolts
    int millivolts = (sensorValue * REFERENCE_MV) / 1023;

    // Calculate and print the corresponding distance
    int distance = getDistance(millivolts);
    Serial.print(distance);
    Serial.println(" cm");

    // Wait before the next measurement
    delay(100);
}