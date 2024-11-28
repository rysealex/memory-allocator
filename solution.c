// Alex Ryse
// solution.c

/*
    command line to compile this program: gcc -o solution *.c -Wall -lm
    command line to execute this program: ./solution (enter the byte requirement here)
*/

#include "allocateMemory.h"

int main(int argc, char *argv[])
{
    // error checking for command line argument, user must only input one value
    if (argc != 2)
    {
        // prompt the user
        printf("Enter exactly one command line argument\n");
        return 0; // exit the program
    }

    // get the memory requirement for a program given by command line input
    int memoryReq = atoi(argv[1]);

    // error checking for command line argument, user must only input a value greater than 0
    if (memoryReq <= 0)
    {
        // prompt the user
        printf("The byte requirement must be greater than 0\n");
        return 0; // exit program
    }

    // display the memory requirement to the user
    printf("The byte requirement: %d\n", memoryReq);

    // intitialize the number of free blocks
    int numFreeBlocks = 0;

    // get the number of free blocks from the user input
    printf("Enter the number of free blocks: ");
    scanf("%d", &numFreeBlocks);

    // error checking for standard user input, user must input at least one free block
    if (numFreeBlocks <= 0)
    {
        // prompt the user
        printf("Enter at least one free block\n");
        return 0; // exit program
    }

    // initialize the blockSizeContainer to hold the size of each free block
    int *blockSizeContainer = createBlockSizeContainer(numFreeBlocks);

    // initialize the sortedUsableBlockContainer to hold the blocks that can be used accordingly in a sorted manner
    // (blocks must be less than or equal to memoryReq to be used)
    int *sortedUsableBlockContainer = createUsableBlockContainer(blockSizeContainer, numFreeBlocks, memoryReq);

    // get size of the sortedUsableBlockContainer
    int containerSize = getContainerSize(sortedUsableBlockContainer, numFreeBlocks, memoryReq);

    // initialize stack2d s2d to hold all possible subsets of sortedUsableBlockContainer
    stack2d s2d = blockSubsets(sortedUsableBlockContainer, containerSize);

    // display all the solution subsets to the user, starting with the best solution first
    findStackSolutions(&s2d, containerSize, memoryReq);

    return 0; // successfully exit the program
}