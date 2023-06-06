import java.io.BufferedWriter;
import java.io.FileWriter;

import processing.serial.*;

String outFilename = "out.txt";

short portIndex = 2;
Serial myPort; 

void setup ()  {
  size(200,200); 
  println(" Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this,Serial.list()[portIndex], 115200);
  myPort.bufferUntil('\n');
}

void draw () { }

void serialEvent (Serial myPort) {
  String rpstr = myPort.readStringUntil('\n');
  if (rpstr != null) {
    String[] list = split(rpstr, ':');
    if(list.length == 10) {
      float ax = float(list[0]);
      float ay = float(list[1]);
      float az = float(list[2]);
      float gx = float(list[3]);
      float gy = float(list[4]);
      float gz = float(list[5]);
      float mx = float(list[6]);
      float my = float(list[7]);
      float mz = float(list[8]);
     
      String output = ax + ";" + ay + ";" + az + ";" + gx + ";" + gy + ";" + gz + ";" + mx + ";" + my + ";" + mz;
      println(output);
      appendTextToFile(outFilename, output);
    }
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
