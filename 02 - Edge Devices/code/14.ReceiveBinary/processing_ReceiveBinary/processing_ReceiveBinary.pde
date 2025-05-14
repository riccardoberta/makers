import processing.serial.*;

Serial myPort; 

// Define the header and the tag for the message
public static final char HEADER = '|';
public static final char MOUSE  = 'M';

void setup(){
  size(200, 400);
  println(" Connecting to -> " + Serial.list()[2]);
  myPort = new Serial(this,Serial.list()[2], 9600);
}

void draw(){ }

// This callback function is called whenever data is received
// and it is used to echoes the received data to the console
void serialEvent(Serial p) {
  String inString = myPort.readStringUntil('\n');
  if(inString != null) {
      println( inString );   
  }
}

// This callback function is called whenever the mouse is pressed
// It gets the x and y coordinates of the mouse and sends them
void mousePressed() {
  int x = mouseX;
  int y = mouseY;
  sendMessage(MOUSE, x, y);
}

// The function sends a header, a tag, x-coordinate as single bytes and
// the y-coordinate as two bytes. 
void sendMessage(char tag, int x, int y) {
  myPort.write(HEADER);
  myPort.write(tag);
  myPort.write(x);
  myPort.write((byte)(y >> 8));  // MSB
  myPort.write((byte)(y & 0xFF)); // LSB
}
