/* Write a C program to implement stack. Stack is a LIFO data strcuture    *
 * LIFO - Last in First Out                                                *
 * Perform PUSH(insert operation), POP(Delete operation) and Display stack */

#include <stdio.h>
//#include <conio.h>
#define MAXSIZE 5

struct stack /* Structure definition for stack */
{
int stk[MAXSIZE];
int top;
};

typedef struct stack STACK;
STACK s;

/* Function declaration/Prototype*/

void push (void);
int pop(void);
void display (void);

void main ()
{
int choice;
int option = 1;

clrscr ();

s.top = -1;

printf ("STACK OPERATION\n");
while (option)
{
printf ("------------------------------------------\n");
printf (" 1 --> PUSH \n");
printf (" 2 --> POP \n");
printf (" 3 --> DISPLAY \n");
printf (" 4 --> EXIT \n");
printf ("------------------------------------------\n");

printf ("Enter your choice\n");
scanf ("%d", &choice);

switch (choice)
{
case 1: push();
break;
case 2: pop();
break;
case 3: display();
break;
case 4: return;
}
git a
fflush (stdin);
printf ("Do you want to continue(Type 0 or 1)?\n");
scanf ("%d", &option);
}
}

/*Function to add an element to the stack*/
void push ()
{
int num;
if (s.top == (MAXSIZE - 1))
{
printf ("Stack is Full\n");
return;
}
else
{
printf ("Enter the element to be pushed\n");
scanf ("%d", &num);
s.top = s.top + 1;
s.stk[s.top] = num;
}
return;
}


/*Function to delete an element from the stack*/
int pop ()
{
int num;
if (s.top == - 1)
{
printf ("Stack is Empty\n");
return (s.top);
}
else
{
num = s.stk[s.top];
printf ("poped element is = %d\n", s.stk[s.top]);
s.top = s.top - 1;
}
return(num);
}

/*Function to display the status of the stack*/
void display ()
{
int i;
if (s.top == -1)
{
printf ("Stack is empty\n");
return;
}
else
{
printf ("\nThe status of the stack is\n");
for (i = s.top; i >= 0; i--)
{
printf ("%d\n", s.stk[i]);
}
}
printf ("\n");
}

/*---------------------------------------------------------------------------
Output
STACK OPERATION
------------------------------------------
1 --> PUSH
2 --> POP
3 --> DISPLAY
4 --> EXIT
------------------------------------------
Enter your choice
1
Enter the element to be pushed
23
Do you want to continue(Type 0 or 1)?
1
------------------------------------------
1 --> PUSH
2 --> POP
3 --> DISPLAY
4 --> EXIT
------------------------------------------
Enter your choice
1
Enter the element to be pushed
45
Do you want to continue(Type 0 or 1)?
1
------------------------------------------
1 --> PUSH
2 --> POP
3 --> DISPLAY
4 --> EXIT
------------------------------------------
Enter your choice
1
Enter the element to be pushed
78
Do you want to continue(Type 0 or 1)?
1
------------------------------------------
1 --> PUSH
2 --> POP
3 --> DISPLAY
4 --> EXIT
------------------------------------------
Enter your choice
3

The status of the stack is
78
45
23

Do you want to continue(Type 0 or 1)?
1
------------------------------------------
1 --> PUSH
2 --> POP
3 --> DISPLAY
4 --> EXIT
------------------------------------------
Enter your choice
2
poped element is = 78
Do you want to continue(Type 0 or 1)?
1
------------------------------------------
1 --> PUSH
2 --> POP
3 --> DISPLAY
4 --> EXIT
------------------------------------------
Enter your choice
3

The status of the stack is
45
23

Do you want to continue(Type 0 or 1)?
0
-----------------------------------------------------------------------------*/
