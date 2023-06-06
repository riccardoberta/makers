import java.io.BufferedWriter;
import java.io.FileWriter;

import processing.serial.*;

String outFilename = "out.txt";

short portIndex = 2;
Serial myPort; 

int pitch = 0;
int roll = 0;

void setup () {
  size(640, 360, P3D); 
  for(int i=0; i<Serial.list().length; i++)
    println(" Port: " + Serial.list()[i]);
    
  println(" Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this,Serial.list()[portIndex], 115200);
  myPort.bufferUntil('\n');
}

void draw () {
  size(640,360,P3D);
  background(0);
  lights();

  pushMatrix();
  translate(width/2, height/2, -30);
  rotateX(((float)pitch)*PI/180.0); 
  rotateZ(((float)roll)*PI/180.0); 
  box(100);
  popMatrix();
}

void serialEvent (Serial myPort) {
  String rpstr = myPort.readStringUntil('\n');
  if (rpstr != null) {
    String[] list = split(rpstr, ':');
    pitch = ((int)float(list[0]));
    roll = ((int)float(list[1]));
    appendTextToFile(outFilename, list[0]);
  }
}

void appendTextToFile(String filename, String text){
  File f = new File(dataPath(filename));
  if(!f.exists()){
    createFile(f);
  }
  try {
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(f, true)));
    out.println(text);
    out.close();
  }catch (IOException e){
      e.printStackTrace();
  }
}

void createFile(File f){
  File parentDir = f.getParentFile();
  try{
    parentDir.mkdirs(); 
    f.createNewFile();
  }catch(Exception e){
    e.printStackTrace();
  }
}    
