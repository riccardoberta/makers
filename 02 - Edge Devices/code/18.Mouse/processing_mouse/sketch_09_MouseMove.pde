
import java.awt.AWTException;
import java.awt.Robot;
import processing.serial.*;

Serial myPort; 
Robot myRobot; 

public static final short LF = 10;        
public static final short portIndex = 2;
public static final char HEADER = 'M';

void setup() { 
  size(200, 200);
  println(" Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this,Serial.list()[portIndex], 9600); 
  try { myRobot = new Robot(); }
  catch (AWTException e) { e.printStackTrace(); }
}

void draw() { }

void serialEvent(Serial p) {
  String message = myPort.readStringUntil(LF); 
  if(message != null) {
    String [] data  = message.split(",");
    if(data[0].charAt(0) == HEADER) {
      if( data.length > 3) {
        int x = Integer.parseInt(data[1]);
        int y = Integer.parseInt(data[2]);
        println("x= " + x + " y= " + y);
        myRobot.mouseMove(x,y); 
      }
    }
  }
}
