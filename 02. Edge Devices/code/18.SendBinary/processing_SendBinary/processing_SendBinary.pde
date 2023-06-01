import processing.serial.*;

Serial myPort;        
short portIndex = 2;  

char HEADER = 'H';
int value1, value2;   

void setup() {
  size(800, 800);
  println(" Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this,Serial.list()[portIndex], 9600);
}

void draw() {
  if ( myPort.available() >= 5) {
    if( myPort.read() == HEADER){
 
      value1 = myPort.read();   
      value1 = myPort.read() * 256 + value1; 

      value2 = myPort.read();                 
      value2 =  myPort.read() * 256 + value2; 

      println("Message received: " + value1 + "," + value2);
    }
  }
  
  background(255);             
  fill(0);                     
  rect(0, 0, value1,value2);
}
