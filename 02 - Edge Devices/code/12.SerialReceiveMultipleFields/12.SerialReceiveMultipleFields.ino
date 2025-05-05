// numbero of expected fields
const int NUMBER_OF_FIELDS = 3;

// current field being received
int field_index = 0;             

// Array to hold velues
int values[NUMBER_OF_FIELDS] = {0,0,0};

void setup() {
    Serial.begin(9600); 
}

void loop() {  
    if( Serial.available()) {
        char ch = Serial.read();
    
        // Accumlate digits to build the value of a field
        if(ch >= '0' && ch <= '9') {
            values[field_index] = (values[field_index] * 10) + (ch - '0'); 
        }
    
        // Comma is our separator, so move on to the next field
        else if (ch == ',' && field_index <= NUMBER_OF_FIELDS){
            Serial.println(ch);
            field_index++;  
        }

        // Any other character ends the acquisition of fields and
        // we provide some feedback, the we set the field to zero
        // to start collecting the new value
        else {
            Serial.print(field_index + 1);
            Serial.println(" fields received:");
            for(int i=0; i <= field_index; i++) {
                Serial.println(values[i]);
                values[i] = 0; 
            }

            // Ready to start over
            field_index = 0;  
        }
    }
}