// Volatile

int LED = 13;
int SW = 2;
int lastCount = -1;
volatile int count = 0;

void handleSW () 
{
   digitalWrite(LED, digitalRead(SW)); 
   count++;
}

void handleOtherStuff() 
{
  if (count != lastCount) 
  {
        Serial.print("Count ");
        Serial.println(count);
        lastCount = count;
  }
}

void setup () 
{
    //Start up the serial port
    Serial.begin(9600);
  
    pinMode (LED, OUTPUT);
    pinMode (SW, INPUT_PULLUP);
    attachInterrupt(INT0, handleSW, CHANGE);
}

void loop () 
{
    handleOtherStuff();
}


