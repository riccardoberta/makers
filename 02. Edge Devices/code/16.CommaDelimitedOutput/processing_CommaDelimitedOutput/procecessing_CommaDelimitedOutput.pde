import processing.serial.*;

// Create object from Serial class
Serial myPort;        

char HEADER = 'H';    
short LF = 10;        
short portIndex = 2;  

void setup() {
  // In Processing, all available serial ports are contained in the Serial.list 
  // object and this example uses the value of a variable called portIndex
  println(" Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this,Serial.list()[portIndex], 9600);
}

// The draw  function in Processing works like loop  
// in Arduino; it is called repeatedly
void draw() {}

void serialEvent(Serial p) {
  
  // Reads serial data
  String message = myPort.readStringUntil(LF);
  
  if(message != null) {
    print(message);
    
    // Uses the Java split() method to create an array 
    // from the comma-separated fields
    String [] data  = message.split(",");
    
    if(data[0].charAt(0) == HEADER) {
      
      // skip the header and terminating cr and lf
      for( int i = 1; i < data.length-1; i++) {
        int value = Integer.parseInt(data[i]);
        println("Value" +  i + " = " + value);
      }
      
      println();
    }
  }
}
