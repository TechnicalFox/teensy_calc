#include <openGLCD.h>

void setup()
{
  
  pinMode(4, INPUT);
  pinMode(13, OUTPUT);
  
  GLCD.Init();
  GLCD.SelectFont(System5x7);
  
  GLCD.print("Pin 4 State: ");  
}

void loop()
{
  GLCD.CursorTo(13, 0);
  int temp = digitalRead(4);
  GLCD.print(temp);
  
  if ( temp == 0 ) {
    digitalWrite(13, HIGH);
    delay(100);
  } else {
    digitalWrite(13, LOW);
  }
  
  GLCD.CursorTo(0, 2);
  GLCD.print(millis());
  
  
}
