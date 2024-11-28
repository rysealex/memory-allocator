// Alex Ryse
// stack.h

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// symbolic constant for maximum size of stack
#define MAX 100

// create a 1D stack
typedef struct stack
{
    int items[MAX];
    int front;
    int rear;
} stack;

// create a 2D stack
typedef struct stack2d
{
    struct stack sItems[MAX];
    int front;
    int rear;

} stack2d;

// function declarations

// initializeStack function
void initializeStack(struct stack *s);

// initializeStack2D function
void initializeStack2D(struct stack2d *s2d);

// push function
void push(struct stack *s, int value);

// push2D function
void push2D(struct stack2d *s2d, struct stack s1d);

// pop function
void pop(struct stack *s);

// traverseStack2D function
void traverseStack2D(struct stack2d *s2d);

// checkFull function
char checkFull(struct stack *s);

// checkFull2D function
char checkFull2D(struct stack2d *s2d);

// isStackEmpty function
char isStackEmpty(struct stack *s);

#endif