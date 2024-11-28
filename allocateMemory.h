// Alex Ryse
// allocateMemory.h

#ifndef ALLOCATEMEMORY_H
#define ALLOCATEMEMORY_H

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

// function declarations

// createBlockSizeContainer function
int *createBlockSizeContainer(int numFreeBlocks);

// sortUsableBlockContainer function
int *sortUsableBlockContainer(int *usableBlockContainer, int containerSize);

// createUsableBlockContainer function
int *createUsableBlockContainer(int *blockSizeContainer, int numFreeBlocks, int memoryReq);

// getContainerSize function
int getContainerSize(int *sortedUsableBlockContainer, int numFreeBlocks, int memoryReq);

// calcBlockSubset function
void calcBlockSubset(int *container, int containerSize, struct stack2d *result, struct stack *subset, int index);

// blockSubsets function
stack2d blockSubsets(int *container, int containerSize);

// findStackSolutions function
void findStackSolutions(struct stack2d *s2d, int containerSize, int memoryReq);

// displayBestSolutions function
void displayBestSolutions(int **solutionsContainer, int containerSize, int numSolutions);

#endif