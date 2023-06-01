import processing.serial.*;

Serial myPort; 
short portIndex = 2;
public static final char HEADER = '|';
public static final char MOUSE  = 'M';

void setup()
{
  size(200, 400);
  println(" Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this,Serial.list()[portIndex], 9600);
}

void draw(){ }

// Echo text string from Arduino
void serialEvent(Serial p) {
  String inString = myPort.readStringUntil('\n');
  if(inString != null) {
      println( inString );   
  }
}

// The window size was set to 200,400, so index
// would fit into a single byte and value would fit into two bytes
void mousePressed() {
  int index = mouseX;
  int value = mouseY;
  sendMessage(MOUSE, index, value);
}

// The function sendMessage sends a header, tag, and index as single bytes. 
// It sends the value as two bytes, with the most significant byte first.
void sendMessage(char tag, int index, int value) {
  myPort.write(HEADER);
  myPort.write(tag);
  myPort.write(index);
  char c = (char)(value / 256); // msb
  myPort.write(c);
  c = (char)(value & 0xff); // lsb
  myPort.write(c);
}
