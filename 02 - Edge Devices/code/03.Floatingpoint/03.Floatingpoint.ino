// Floatingpoint 
// Demonstrate well-known round-off error problem with 
// floating point arithmetic

void setup() {
    // define the variables
    float w,x,y,z;
  
    Serial.begin(9600);
    delay(2500);           
  
    // 4.0 / 3.0 gives an approximation of 1.333..., which is not exactly 4/3, 
    // as floating-point numbers cannot always represent exact decimal values.
    w = 4.0/3.0;

    // w - 1 results in 0.333...
    x = w - 1;

    //3 * x results in 0.999..., which should theoretically equal 1, 
    // but due to the floating-point approximation, it is just shy of 1.
    y = 3*x;
  
    // 1 - y results in a small value close to zero, which demonstrates 
    // the rounding error introduced in the earlier steps
    z = 1 - y;

    // Print the values of w, x, y, and z to the serial monitor
    // using two-parameter verson of Serial.print(), the second parameter 
    // specifies the number of digits in value sent to the Serial Monitor
  
    Serial.println("\nFloating point arithmetic test"); 
    Serial.println(w,16);  
    Serial.println(x,8);  
    Serial.println(y,8);  
    Serial.println(z,8);  

    // Prints z multiplied by a big number to better visualize the effect of 
    // the round-off error when scaling up the small floating-point value
    Serial.println(z*1.0e7,8);  
}

void loop() {}     
