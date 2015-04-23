#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXSIZE 100

/////////////////////////////////////////////////////////////////////////////////////////
//STACK IMPLIMENTATION//
/////////////////////////////////////////////////////////////////////////////////////////

struct stack {
  char list[MAXSIZE];
  int top;
};

typedef struct stack STACK;
STACK operatorStack;

/*Function to push an element to the stack*/
void push (char pushed) {
  if ( operatorStack.top < (MAXSIZE - 1) ) {
    operatorStack.top++;
    operatorStack.list[operatorStack.top] = pushed;
    //Serial.printf("%c pushed to stack\n", pushed);
  } else {
    //Serial.printf("ERROR: stack full\n");
  }
  return;
}

/*Function to pop an element from the stack*/
char pop () {
  char popped = NULL;
  if ( operatorStack.top > -1 ) { 
    popped = operatorStack.list[operatorStack.top];
    operatorStack.top--;
    //Serial.printf("%c popped from stack\n");
  } else {
    //Serial.printf("ERROR: can't pop from empty stack\n");
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
  int head;
  int tail;
  int count;
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
    //Serial.printf("ERROR: queue full\n");
    return;
  }
  outputQueue.list[outputQueue.tail] = added;
  outputQueue.count++;
  //Serial.printf("%c added to queue\n", added);
  return;
}

/*Function to remove and return an element from the queue, remove is a keyword*/
char rem () {
  char removed = NULL;
  if ( outputQueue.count > 0 ) {
    removed = outputQueue.list[outputQueue.head];
    outputQueue.count--;
    //Serial.printf("%c removed from queue\n", removed);
    if ( outputQueue.head < (MAXSIZE - 1) ) {
      outputQueue.head++;
    } else {
      outputQueue.head = 0;
    }
  } else {
    //Serial.printf("ERROR: can't remove from empty queue");
  }
  return removed;
}

/////////////////////////////////////////////////////////////////////////////////////////
//END QUEUE IMPLIMENTATION//
/////////////////////////////////////////////////////////////////////////////////////////

char curFunction[MAXSIZE] = {NULL};
int curFunctionCount = 0;

char operators[7] = {'^','*','/','+','-','(',')'};
char numbers[10] = {'1','2','3','4','5','6','7','8','9','0'};

typedef enum { false, true } bool;

void evaluate() {
  
  return;
}

void testList(char curPressed) {
      if ( curFunctionCount < MAXSIZE && curPressed != '\t' && curPressed != '\n') {
        curFunction[curFunctionCount] = curPressed;
        curFunctionCount++;
        //Serial.printf("%c added to current function array\n", curPressed);
      } else if ( curPressed == '\n' ) {
        evaluate();
      } else if ( curPressed == '\t' ) {
        //ignore for mode button
      } else {
        //Serial.printf("ERROR: function char array full\n");
      }
}

void printFunction() {
    int i = 0;
    while ( i < curFunctionCount ) {
        printf("%c", curFunction[i]);
        i++;
    }
    printf("\n");
}

bool isNum(char c) {
    bool num = false;
    int i = 0;
    while ( i < 10 ) {
        if ( c == numbers[i] ) {
            num = true;
        }
        i++;
    }
    return num;
}

bool isOper(char c) {
    bool oper = false;
    int i = 0;
    while ( i < 7 ) {
        if ( c == operators[i] ) {
            oper = true;
        }
        i++;
    }
    return oper;
}

int charToInt(char c) {
    int i = NULL;
    switch (c) {
        case '1':
            i = 1;
            break;
        case '2':
            i = 2;
            break;
        case '3':
            i = 3;
            break;
        case '4':
            i = 4;
            break;
        case '5':
            i = 5;
            break;
        case '6':
            i = 6;
            break;
        case '7':
            i = 7;
            break;
        case '8':
            i = 8;
            break;
        case '9':
            i = 9;
            break;
        case '0':
            i = 0;
            break;
    }
    return i;
}

void fillQueue() {
    int i = 0;
    int lastNum = 0; //was the last char a number?
    while ( i < curFunctionCount ) {
        char curChar = curFunction[i];
        if ( isNum(curChar) ) {
            if ( lastNum == 0 ) {
                lastNum = charToInt(curChar);
            } else {
                lastNum = ((lastNum * 10) + charToInt(curChar));
            }
            lastNum++;
        } else if ( isOper(curChar) ) {
            add(lastNum);
            lastNum = 0;
            if ( curChar != ')' ) {
                char curOper = NULL;
                curOper = look();
                while ( curOper != '(' && curOper != NULL) {
                    add(pop()); //pop off stack into queue
                    curOper = look();
                }
                if ( curOper == ')' ) {
                    pop();
                } else {
                    //Serial.printf("SYNTAX ERROR");
                }
            } else {
                push(curChar);
            }
        }
        i++;
    }
    i = 0;
    while ( i < operatorStack.top + 1 ) {
        add(pop());
        i++;
    }
}

double evalFunction() {
    double result = 0.0;
    int i = 0;
    while ( i < outputQueue.count ) {
        
    }
}

void main() {
    operatorStack.top = -1;
    outputQueue.head = -1;
    outputQueue.tail = -1;
    outputQueue.count = 0;
    testList('1');
    testList('4');
    testList('+');
    testList('5');
    //printFunction();

    //double result = NULL;
    //result = evalFunction();
    //printf("%d\n", result);

    // + 43
    // - 45
    // * 42
    // / 47
    // ^ 94
    // ( 40
    // ) 41
    char x = ')';
    int y = (int)x;
    printf("%i\n", y);
}
