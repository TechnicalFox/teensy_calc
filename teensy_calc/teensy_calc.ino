#include <stdio.h>
#include <string.h>
#include <math.h>
#include <IRremote.h>
#include <openGLCD.h>

#define MAXSIZE 100

/////////////////////////////////////////////////////////////////////////////////////////
//STACK IMPLIMENTATION//
/////////////////////////////////////////////////////////////////////////////////////////

struct stack {
  char list[MAXSIZE];
  int top = -1;
};

typedef struct stack STACK;
STACK operatorStack;

/*Function to push an element to the stack*/
void push (char pushed) {
  if ( operatorStack.top < (MAXSIZE - 1) ) {
    operatorStack.top++;
    operatorStack.list[operatorStack.top] = pushed;
    Serial.printf("%c pushed to stack\n", pushed);
  } else {
    Serial.printf("ERROR: stack full\n");
  }
  return;
}

/*Function to pop an element from the stack*/
char pop () {
  char popped = NULL;
  if ( operatorStack.top > -1 ) { 
    popped = operatorStack.list[operatorStack.top];
    operatorStack.top--;
    Serial.printf("%c popped from stack\n");
  } else {
    Serial.printf("ERROR: can't pop from empty stack\n");
  }
  return popped;
}

/*Function to peek at an element form the stack, peek is a keyword*/
char look () {
  char looked = NULL;
  looked = operatorStack.list[operatorStack.top];
  return looked;
}

/////////////////////////////////////////////////////////////////////////////////////////
//END STACK IMPLIMENTATION//
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//QUEUE IMPLIMENTATION//
/////////////////////////////////////////////////////////////////////////////////////////

struct queue {
  char list[MAXSIZE];
  int head = -1;
  int tail  = -1;
  int count = 0;
};

typedef struct queue QUEUE;
QUEUE outputQueue;

/*Function to add an element to the queue*/
void add (char added) {
  if ( outputQueue.head == -1 && outputQueue.tail == -1 ) {
    outputQueue.head = 0;
    outputQueue.tail = 0;
  } else if ( outputQueue.tail == (MAXSIZE - 1) && outputQueue.head != 0 ) {
    outputQueue.tail = 0;
  } else if ( outputQueue.count < (MAXSIZE - 1) ){
    outputQueue.tail++;
  } else {
    Serial.printf("ERROR: queue full\n");
    return;
  }
  outputQueue.list[outputQueue.tail] = added;
  outputQueue.count++;
  Serial.printf("%c added to queue\n", added);
  return;
}

/*Function to remove and return an element from the queue, remove is a keyword*/
char rem () {
  char removed = NULL;
  if ( outputQueue.count > 0 ) {
    removed = outputQueue.list[outputQueue.head];
    outputQueue.count--;
    Serial.printf("%c removed from queue\n", removed);
    if ( outputQueue.head < (MAXSIZE - 1) ) {
      outputQueue.head++;
    } else {
      outputQueue.head = 0;
    }
  } else {
    Serial.printf("ERROR: can't remove from empty queue");
  }
  return removed;
}

/////////////////////////////////////////////////////////////////////////////////////////
//END QUEUE IMPLIMENTATION//
/////////////////////////////////////////////////////////////////////////////////////////

int IRpin = 4;
char lastPressed = NULL;
char currentFunction[MAXSIZE] = {NULL};
int currentFunctionCount = 0;

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
      if ( currentFunctionCount < MAXSIZE && curPressed != '\t' && curPressed != '\n') {
        currentFunction[currentFunctionCount] = curPressed;
        currentFunctionCount++;
        Serial.printf("%c added to current function array\n", curPressed);
      } else if ( curPressed == '\n' ) {
        evaluate();
      } else if ( curPressed == '\t' ) {
        //ignore for mode button
      } else {
        Serial.printf("ERROR: function char array full\n");
      }
    }
    if ( curPressed != NULL && curPressed != '\t' ) {
      GLCD.printf("%c", curPressed);
    }
    delay(50);
    irrecv.resume();   // Receive the next value
  }
}

