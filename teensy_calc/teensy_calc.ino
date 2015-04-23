#include <stdio.h>
#include <string.h>
#include <math.h>
#include <IRremote.h>
#include <openGLCD.h>

int IRpin = 4;
char lastPressed = NULL;
char currentLine[100] = {NULL};

IRrecv irrecv(IRpin);
decode_results results;

void setup() {
  GLCD.Init();
  GLCD.SelectFont(System5x7);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void getPressed(char *curPressed) {
  switch(results.value) {
      case 0xffffffff :
        *curPressed = lastPressed;
        break;
      case 0xffa25d :
        *curPressed = '\n';
        lastPressed = '\n';
        break;
      case 0xff629d :
        *curPressed = '\t';
        lastPressed = '\t';
        break;
      case 0xffe21d :
        if ( lastPressed == '\t' ) {
          *curPressed = 'y';
          lastPressed = 'y';
        } else {
          *curPressed = 'x';
          lastPressed = 'x';
        }
        break;
      case 0xff22dd :
        *curPressed = '^';
        lastPressed = '^';
        break;
      case 0xff02fd :
        *curPressed = '(';
        lastPressed = '(';
        break;
      case 0xffc23d :
        *curPressed = ')';
        lastPressed = ')';
        break;
      case 0xffe01f :
        *curPressed = '=';
        lastPressed = '=';
        break;
      case 0xffa857 :
        *curPressed = '-';
        lastPressed = '-';
        break;
      case 0xff906f :
        *curPressed = '+';
        lastPressed = '+';
        break;
      case 0xff6897 :
        *curPressed = '0';
        lastPressed = '0';
        break;
      case 0xff9867 :
        *curPressed = '*';
        lastPressed = '*';
        break;
      case 0xffb04f :
        *curPressed = '/';
        lastPressed = '/';
        break;
      case 0xff30cf :
        *curPressed = '1';
        lastPressed = '1';
        break;
      case 0xff18e7 :
        *curPressed = '2';
        lastPressed = '2';
        break;
      case 0xff7a85 :
        *curPressed = '3';
        lastPressed = '3';
        break;
      case 0xff10ef :
        *curPressed = '4';
        lastPressed = '4';
        break;
      case 0xff38c7 :
        *curPressed = '5';
        lastPressed = '5';
        break;
      case 0xff5aa5 :
        *curPressed = '6';
        lastPressed = '6';
        break;
      case 0xff42bd :
        *curPressed = '7';
        lastPressed = '7';
        break;
      case 0xff4ab5 :
        *curPressed = '8';
        lastPressed = '8';
        break;
      case 0xff52ad :
        *curPressed = '9';
        lastPressed = '9';
        break;
      default :
        *curPressed = NULL;
        break;
    }
    return;
}

void evaluate() {
  
  return;
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    //results.decode_type:
    //NEC     =  1
    //SONY    =  2
    //RC5     =  3
    //RC6     =  4
    //UNKNOWN = -1
    char curPressed = NULL;
    if ( results.decode_type == 1 ) {
      getPressed(&curPressed);
      Serial.printf("curPressed = %c\n", curPressed);
    }
    if ( curPressed != NULL && curPressed != '\t' ) {
      GLCD.printf("%c", curPressed);
    }
    delay(50);
    irrecv.resume();   // Receive the next value
  }
}

