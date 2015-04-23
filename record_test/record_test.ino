#include <stdio.h>
#include <IRremote.h>
#include <openGLCD.h>

int IRpin = 4;

IRrecv irrecv(IRpin);
decode_results results;

void setup()
{
  GLCD.Init();
  GLCD.SelectFont(System5x7);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    //results.decode_type:
    //NEC     =  1
    //SONY    =  2
    //RC5     =  3
    //RC6     =  4
    //UNKNOWN = -1
    GLCD.printf("Hex value: %x\nType: %i\n\n", results.value, results.decode_type);
    
    int i = 0;
    while ( i < results.rawlen ) {
      Serial.print(results.rawbuf[i]);
      i++;
    }
    Serial.print("\n");
    irrecv.resume();   // Receive the next value
  }
}

