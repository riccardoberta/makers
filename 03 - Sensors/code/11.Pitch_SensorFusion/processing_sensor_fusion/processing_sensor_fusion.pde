import processing.serial.*;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.Locale;

// Output filename for storing pitch values
String outFilename = "out.csv";  

// Serial object for communication
Serial myPort;            

// Variable to store the pitch value
float pitch_acc = 0;
float pitch_gyro = 0;
float pitch = 0;

void setup() {
    // Set up the canvas size and 3D renderer    
    size(640, 360, P3D);            
    
    // Initialize serial communication with the port
    myPort = new Serial(this, Serial.list()[2], 115200);  
    myPort.bufferUntil('\n'); 
}

void draw() {

    // Clear the screen with a black background
    background(0);  
    
    // Add lighting to the scene
    lights();       

    // Apply 3D transformations and rotate the box based on pitch
    pushMatrix();
    translate(width / 2, height / 2, -30);  // Move the box to the center of the canvas
    rotateX(radians(pitch));  // Rotate the box on the X axis using the pitch value
    box(100);  // Draw the box with a size of 100 pixels
    popMatrix();  // Restore the previous transformation state
}

void serialEvent(Serial myPort) {    
    // Read the incoming data until a newline character
    String rpstr = myPort.readStringUntil('\n');
    //print(rpstr);
    
    // Check if the data is not null
    if (rpstr != null) {  
        // Split the data into an array using ':' as delimiter
        String[] list = split(rpstr, ":");   //<>//
               
        if(list.length == 4) {
          try {            
              // Parse the pitch value from the received data
              pitch_acc = float(list[1]);  
              pitch_gyro = float(list[2]); 
              pitch = float(list[3]); 

              // Append to the file
              appendTextToFile(outFilename, pitch_acc, pitch_gyro, pitch);
          } 
          // Catch and ignore any exceptions in case of malformed data
          catch (Exception ex) {
            println(ex);
          }
        }
    }
}

void appendTextToFile(String filename, float pitch_acc, float pitch_gyro, float pitch) {
  
    // Set up the locale for countries that use ',' as a decimal separator
    DecimalFormatSymbols symbols = new DecimalFormatSymbols(Locale.ITALY);
    DecimalFormat df = new DecimalFormat("#0.00", symbols);

    // Try to open the file and write the text to it
    try (BufferedWriter out = new BufferedWriter(new FileWriter(dataPath(filename), true))) {
        out.write(df.format(pitch_acc));  // Write the pitch to the file
        out.write(";");
        out.write(df.format(pitch_gyro));
        out.write(";");
        out.write(df.format(pitch));
        out.newLine();     // Add a new line after each entry
    } 
    catch (IOException e) {
        e.printStackTrace();  // Print any errors that occur while writing the file
    }
}
