import processing.serial.*;

Serial myPort;

void setup() {
  size(200, 200);
  myPort = new Serial(this, Serial.list()[2], 9600);
}

void draw() {
  if (myPort.available() > 0) {  
    int value = myPort.read();        
    background(255);
    println(value);
    line(0, 226-value, 200, 226-value);           
  }
}
