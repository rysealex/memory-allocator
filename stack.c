// Alex Ryse
// stack.c

#include "stack.h"

// function definitions

// initializeStack function
void initializeStack(struct stack *s)
{
    // fill the stack with all 0's
    memset(s->items, 0, sizeof(int) * MAX);
    s->rear = 0; // set rear to 0
}

// initializeStack2D function
void initializeStack2D(struct stack2d *s2d)
{
    // fill the 2D stack with all 0's
    memset(s2d->sItems, 0, sizeof(stack) * MAX);
    s2d->rear = 0; // set rear to 0
}

// push function
void push(struct stack *s, int value)
{
    // if stack is full
    if (!checkFull(s))
    {
        // prompt the user
        printf("Stack is full\n");
        exit(0); // exit the program
    }
    // push current value on top of stack
    s->items[s->rear] = value;
    s->rear++; // increment rear
}

// push2D function
void push2D(struct stack2d *s2d, struct stack s1d)
{
    // if 2D stack is full
    if (!checkFull2D(s2d))
    {
        // prompt the user
        printf("Stack is full\n");
        exit(0); // exit the program
    }
    // push current value on top of 2D stack
    s2d->sItems[s2d->rear] = s1d;
    s2d->rear++; // increment rear
}

// pop function
void pop(struct stack *s)
{
    // if stack is empty
    if (!isStackEmpty(s))
    {
        // prompt the user
        printf("Stack is empty\n");
        exit(0); // exit the program
    }
    // replace the most recent value in the stack with a 0
    s->items[s->rear] = 0;
    s->rear--; // decrement rear
}

// traverseStack2D function
void traverseStack2D(struct stack2d *s2d)
{
    // iterate through stack2d s2d and display all elements
    for (int i = 0; i <= s2d->rear; i++)
    {
        for (int j = 0; j <= s2d->sItems[i].rear; j++)
        {
            printf("%d ", s2d->sItems[i].items[j]);
        }
        printf("\n");
    }
}

// checkFull function
char checkFull(struct stack *s)
{
    // if stack rear is larger than maximum size of stack
    if (s->rear >= MAX)
    {
        return 0; // false
    }
    return 1; // true
}

// checkFull2D function
char checkFull2D(struct stack2d *s2d)
{
    // if stack rear is larger than maximum size of 2D stack
    if (s2d->rear >= MAX)
    {
        return 0; // false
    }
    return 1; // true
}

// isStackEmpty function
char isStackEmpty(struct stack *s)
{
    // if stack rear is less than 0
    if (s->rear < 0)
    {
        return 0; // false
    }
    return 1; // true
}