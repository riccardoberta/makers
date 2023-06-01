// Processing sketch to draw line that follows nunchuck data
import processing.serial.*;

Serial myPort;
public static final short portIndex = 2;

void setup()
{
  size(200, 200);
  myPort = new Serial(this, Serial.list()[portIndex], 9600);
}

void draw()
{
  if ( myPort.available() > 0) {  
    int y = myPort.read();        
    background(255);
    println(y);
    line(0,63-y,127,y);           
  }
}
