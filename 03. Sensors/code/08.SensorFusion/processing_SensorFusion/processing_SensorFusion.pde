// The screen can be paused using the spacebar
// 'a' starts recording the values in a file
// 'b' stops recording.

import processing.serial.*;

PrintWriter output;

String outputBuff = "";
int value[] = new int[6];
int NEWLINE = 10;
String mode="RUN";
int n;
float scaling = 2;
Serial port;

void setup() {
  size(800,600, P3D);
  port = new Serial(this, Serial.list()[1], 115200);
  port.bufferUntil('\n');
  background(255);
}

void draw() {
  outputBuff="" + millis();
  for(int z=0;z<6;z++) { outputBuff += ("," + value[z]); }
  if (mode=="RECORD") output.println(outputBuff);
  
  background(0);
  lights();
  lights();
  pushMatrix();
  translate(width/2, height/2, -30);
  //rotateZ(((float)value[0])*PI/180.0);
  //rotateX(((float)value[1])*PI/180.0); 
  //rotateZ(((float)value[2])*PI/180.0);
  //rotateX(((float)value[3])*PI/180.0); 
  rotateZ(((float)value[4])*PI/180.0);
  rotateX(((float)value[5])*PI/180.0); 
  box(100);
  popMatrix();
}
 
void serialEvent(Serial port) { 
  String rpstr = port.readStringUntil('\n'); //<>//
  if (rpstr != null) {
    String[] list = split(rpstr, ':');
    if(list.length == 7) { 
      value[0] = (int)(float(list[0]) * scaling); 
      value[1] = (int)(float(list[1]) * scaling);
      value[2] = (int)(float(list[2]) * scaling);
      value[3] = (int)(float(list[3]) * scaling);
      value[4] = (int)(float(list[4]) * scaling);
      value[5] = (int)(float(list[5]) * scaling);
      
      println("pitchAcc : "  + value[0] + "\t" +
              "rollAcc : "   + value[1] + "\t" +
              "pitchGyro : " + value[2] + "\t" +
              "rollGyro : "  + value[3] + "\t" +
              "pitch : "     + value[4] + "\t" +
              "roll : "      + value[5]);
    }
  }
}

void keyPressed() {
  if (key=='a' && mode!="RECORD")  {
    mode="RECORD";
    output = createWriter("values.txt");
  }
  if (key=='b') {
    mode="STOP";
    output.flush();
    output.close();
  }
}
