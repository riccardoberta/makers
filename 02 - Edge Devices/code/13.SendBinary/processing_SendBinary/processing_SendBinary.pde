import processing.serial.*;

Serial myPort;        
short portIndex = 2;  

char HEADER = 'H';
int value;   

void setup() {
  size(800, 800); // Window size
  println("Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this, Serial.list()[portIndex], 9600);
}

void draw() {
  // Wait until at least 3 bytes are available (header + 2 bytes for the integer)
  if (myPort.available() >= 3) {
    if (myPort.read() == HEADER) { // Check for the header character
      int low = myPort.read();    // Read the low byte
      int high = myPort.read();   // Read the high byte
      
      // Reconstruct the 16-bit integer
      value = (high << 8) | low; 

      println("Message received: " + value);
    }
  }
  
  // Visualize the received value
  background(255);               // Clear the background
  fill(0);                       // Black fill color
  rect(0, 0, value, value);      // Draw a square with size based on `value`
}
