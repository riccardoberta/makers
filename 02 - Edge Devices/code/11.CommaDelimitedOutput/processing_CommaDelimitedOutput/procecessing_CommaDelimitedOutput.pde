// imports the Serial class from the processing.serial library
import processing.serial.*;

// Serial port object
Serial myPort;    
int portIndex = 2;

// Buffer to store received data
String received_data;

// Parsed data
float temperature = 0.0;
float humidity = 0.0;
float pressure = 0.0;

void setup() {
    // Set up the application window
    size(400, 200);
    
    // Connect to the right port (the one that the Arduino is connected to):  
    println(" Connecting to -> " + Serial.list()[2]);
    myPort = new Serial(this,Serial.list()[portIndex], 9600);
}

void draw() {
    // Write the received data to the screen
    background(0);
    text("Temperature: " + temperature, 10, 50);
    text("Humidity: " + humidity, 10, 60);
    text("Pressure: " + pressure, 10, 70);
}

// This method is called whenever data is received from the serial port
void serialEvent(Serial p) {
  
    // Read data until newline character
    received_data = myPort.readStringUntil('\n');
  
    // If data is received, parse the data by splitting the
    // received string
    if (received_data != null) {
        String[] fields = split(received_data, ',');
        
        System.out.println(fields[0]);
        
        // check the header
        if (fields[0].equals("H")) {
          temperature = float(fields[1]);
          humidity = float(fields[2]);
          pressure = float(fields[3]);
        }
    }
}
