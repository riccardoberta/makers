const int sensorPin = 0;  // the analog pin connected to the sensor
const long referenceMv = 5000; // long int to prevent overflow when multiplied

void setup() {
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(sensorPin);
  int mV = (val * referenceMv) / 1023;
  Serial.print(mV);
  Serial.print("mV");

  Serial.print(", ");
  int cm = getDistance(mV);
  Serial.print(cm);
  Serial.println("cm");
  
  delay(100);
}

// the following is used to interpolate the distance from a table
// table entries are distances in steps of 250 millivolts
const int TABLE_ENTRIES = 12;  // The numebr of entries in the distance table
const int INTERVAL      = 250; // millivolts seperating each table entry
                                
static int distance[TABLE_ENTRIES] = {150,140,130,100,60,50,40,35,30,25,20,15};  // distance in cm for each 250mv

int getDistance(int mV) {
   if( mV >  INTERVAL * TABLE_ENTRIES-1 )
      return distance[TABLE_ENTRIES-1];
   else {
      int index = mV / INTERVAL;
      float frac = (mV % 250) / (float)INTERVAL;
      return distance[index] - ((distance[index] - distance[index+1]) * frac);
   }
}