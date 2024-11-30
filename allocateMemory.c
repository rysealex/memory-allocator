// Alex Ryse
// allocateMemory.c

#include "allocateMemory.h"

// function definitions

// createBlockSizeContainer function
int *createBlockSizeContainer(int numFreeBlocks)
{
    // initialize the blockSizeContainer to hold the size of each free block
    int *blockSizeContainer = (int *)malloc(numFreeBlocks * sizeof(int));
    // iteratete through each free block to get the size
    for (int i = 0; i < numFreeBlocks; i++)
    {
        // prompt the user for the size of the current block
        printf("Enter the size of block %d: ", i + 1);
        scanf("%d", &blockSizeContainer[i]); // get the user input

        // error checking for standard user input, user must input block sizes greater than 0
        if (blockSizeContainer[i] <= 0)
        {
            // prompt the user
            printf("Block sizes must be greater than 0\n");
            exit(0); // exit program
        }
    }
    return blockSizeContainer; // the blockSizeContainer holding the size of each free block
}

// sortUsableBlockContainer function
int *sortUsableBlockContainer(int *usableBlockContainer, int containerSize)
{
    // initialize tempBlock
    int tempBlock = 0; // to temporarily hold the block that is going to be swapped

    // sort the block sizes from smallest to largest
    for (int i = 0; i < containerSize - 1; i++)
    {
        // check each block size for the smallest block
        for (int j = i + 1; j < containerSize; j++)
        {
            // if current block is greater than another block (smaller block)
            if (usableBlockContainer[i] > usableBlockContainer[j])
            {
                // swap current block with the smaller block
                tempBlock = usableBlockContainer[i];               // set tempBlock to current block
                usableBlockContainer[i] = usableBlockContainer[j]; // update current block with the smaller block
                usableBlockContainer[j] = tempBlock;               // update smaller block with tempBlock (current block)
            }
        }
    }
    return usableBlockContainer; // return the sorted usableBlockContainer
}

// createUsableBlockContainer function
int *createUsableBlockContainer(int *blockContainer, int numFreeBlocks, int memoryReq)
{
    // initialize tempCount
    int tempCount = 0; // to count the number of blocks that can be used depending on the memory requirement (memoryReq)

    // find which blocks can be used to count the size of the new temporary container
    for (int i = 0; i < numFreeBlocks; i++)
    {
        // if current block size is less than or equal to the memory requirment (memoryReq)
        if (blockContainer[i] <= memoryReq)
        {
            tempCount++; // increment tempCount
        }
    }

    // initialize a new temporary container with the adjusted size (tempCount) for holding the memory blocks that can be used
    int *tempContainer = (int *)malloc(tempCount * sizeof(int));
    tempCount = 0; // reset the tempCount

    // find which blocks can be used to add to the new temporary container
    for (int i = 0; i < numFreeBlocks; i++)
    {
        // if current block size is less than or equal to the memory requirment (memoryReq)
        if (blockContainer[i] <= memoryReq)
        {
            // add current block
            tempContainer[tempCount] = blockContainer[i];
            tempCount++; // increment tempCount
        }
    }

    // de-allocate memory in blockContainer
    free(blockContainer);

    // return the invoked sortUsableBlockContainer function (a sorted representation of usableBlockContainer)
    return sortUsableBlockContainer(tempContainer, tempCount);
}

// getContainerSize function
int getContainerSize(int *sortedUsableBlockContainer, int numFreeBlocks, int memoryReq)
{
    // initialize containerSize
    int containerSize = 0; // to hold the size of sortedUsableBlockContainer

    // check whether all free blocks can be used accordingly or not
    for (int i = 0; i < numFreeBlocks; i++)
    {
        // if current block size is less than or equal to memoryReq and greater than zero
        if (sortedUsableBlockContainer[i] <= memoryReq && sortedUsableBlockContainer[i] > 0)
        {
            // current block can be used
            containerSize++; // increment containerSize
        }
    }
    return containerSize; // the size of sortedUsableBlockContainer
}

// calcBlockSubset
void calcBlockSubset(int *container, int containerSize, struct stack2d *result, struct stack *subset, int index)
{
    // push the current subset stack to result 2D stack
    push2D(result, *subset);

    // generate subsets by recursively including and excluding elements
    for (int i = index; i < containerSize; i++)
    {
        // push the current element to subset stack
        push(subset, container[i]);

        // recursively generate subsets with the current element included
        calcBlockSubset(container, containerSize, result, subset, i + 1);

        // pop the current element from the subset (backtracking)
        pop(subset);
    }
}

// blockSubsets function
stack2d blockSubsets(int *container, int containerSize)
{
    // initialize stack2d s2d
    struct stack2d s2d;
    initializeStack2D(&s2d); // initialize s2d with all 0's

    // initialize stack s
    struct stack s;
    initializeStack(&s); // initialize s with all 0's

    // intialize index
    int index = 0;

    // invoke the calcSubset function to calculate all possible subsets from the container
    calcBlockSubset(container, containerSize, &s2d, &s, index);

    // de-allocate memory in container
    free(container);

    return s2d; // all the possible block subsets from the container
}

// displayBestSolutions function
void displayBestSolutions(int **solutionsContainer, int containerSize, int numSolutions)
{
    // calculate the number of possible subsets from the container (2^N, where N is containerSize)
    int subsetSize = pow(2, containerSize); // this is the rows of the solutionsContainer

    // initialize sizeCount, sizeTracker, and rowIndexTracker
    int sizeCount = 0, sizeTracker = -1, rowIndexTracker = -1; // used for keeping count and tracking important references

    // initialize solutionsFlag
    char solutionsFlag = 0; // to indicate if a solution has been found or not (0 is false, 1 is true)

    // iterate through solutionsContainer to check for the best possible solution subset
    for (int i = 0; i < subsetSize; i++)
    {
        for (int j = 0; j < containerSize; j++)
        {
            // if current element in solutionsContainer is empty set (0 is empty set)
            if (solutionsContainer[i][j] == 0)
            {
                break; // skip to next outer loop iteration
            }
            sizeCount++; // increment sizeCount
        }

        // if a best possible solution subset has been found for the first time
        if (!solutionsFlag && sizeCount > 0)
        {
            sizeTracker = sizeCount; // update sizeTracker with current sizeCount
            rowIndexTracker = i;     // get reference to the best solution index in the solutionsContainer
            solutionsFlag = 1;       // flip solutionsFlag
        }

        // if a best possible solution subset has been found again and is better than the previous best
        else if (sizeCount < sizeTracker && sizeCount > 0)
        {
            sizeTracker = sizeCount; // update sizeTracker with current sizeCount
            rowIndexTracker = i;     // get reference to the best solution index in the solutionsContainer
        }
        sizeCount = 0; // reset sizeCount
    }

    // check first if there are no solutions (solutionsFlag is still false)
    if (!solutionsFlag)
    {
        // prompt the user
        printf("\nTHERE ARE NO SOLUTIONS :(\n");
        return (void)0; // exit this function
    }

    // initialize blockCount
    int blockCount = 0; // to track the number of blocks in each solution subset

    // display the best solution first
    printf("\nTHE BEST SOLUTION:\n");
    for (int j = 0; j < containerSize; j++)
    {
        // if current element in solutionsContainer is emtpy set (0 is empty set)
        if (solutionsContainer[rowIndexTracker][j] == 0)
        {
            break; // skip to next outer loop iteration
        }
        blockCount++; // increment blockCount

        // display each block and their size of the best solution subset
        printf("Block #%d of size %d bytes\n", blockCount, solutionsContainer[rowIndexTracker][j]);
    }
    printf("\n");

    blockCount = 0;    // reset blockCount
    solutionsFlag = 0; // reset solutionsFlag

    // display the rest of the solutions if there are any
    printf("THE OTHER SOLUTION(s):\n");
    for (int i = 0; i < subsetSize; i++)
    {
        for (int j = 0; j < containerSize; j++)
        {
            // if current element in solutionsContainer is emtpy set (0 is empty set)
            if (solutionsContainer[i][j] == 0)
            {
                break; // skip to next outer loop iteration
            }

            // if current row is at the best solution subset row
            else if (i == rowIndexTracker)
            {
                break; // skip to next outer loop iteration
            }
            blockCount++;      // increment blockCount
            solutionsFlag = 1; // flip solutionsFlag

            // display each block and their size of the other solution subset
            printf("Block #%d of size %d bytes\n", blockCount, solutionsContainer[i][j]);
        }

        // if a solution subset was found (solutionsFlag is flipped to true)
        if (solutionsFlag)
        {
            printf("\n"); // for user visualization
        }
        solutionsFlag = 0; // reset solutionsFlag
        blockCount = 0;    // reset blockCount
    }
}

void findStackSolutions(struct stack2d *s2d, int containerSize, int memoryReq)
{
    // calculate the number of possible subsets from the container (2^N, where N is containerSize)
    int subsetSize = pow(2, containerSize); // this is the rows of the blockSubsetsContainer

    // initialize subsetTotal
    int subsetTotal = 0; // to hold the total size of each block subset

    // initialize numSolutions
    int numSolutions = 0; // to track the total number of block subset solutions

    // allocate memory for the 2d dynamic array solutionsContainer
    int **solutionsContainer = (int **)malloc(subsetSize * sizeof(int *)); // allocating rows
    for (int i = 0; i < subsetSize; i++)
    {
        solutionsContainer[i] = (int *)malloc(containerSize * sizeof(int)); // allocating columns
        memset(solutionsContainer[i], 0, containerSize * sizeof(int));      // fill with zeros
    }

    // iterate through the stack2d s2d to check for possible solutions
    for (int i = 0; i <= s2d->rear; i++)
    {
        for (int j = 0; j <= s2d->sItems[i].rear; j++)
        {
            // if current element in s2d is empty set (0 is empty set)
            if (s2d->sItems[i].items[j] == 0)
            {
                break; // skip to next outer loop iteration
            }
            subsetTotal += s2d->sItems[i].items[j]; // add current element to subsetTotal
        }

        // if subsetTotal is exactly equal to memoryReq (this is a solution)
        if (subsetTotal == memoryReq)
        {
            numSolutions++; // increment numSolutions

            // iterate to add s2d block subsets to solutionsContainer
            for (int j = 0; j < containerSize; j++)
            {
                // if current element in s2d is empty set (0 is empty set)
                if (s2d->sItems[i].items[j] == 0)
                {
                    break; // skip to next outer loop iteration
                }
                // add current element in s2d to solutionsContainer
                solutionsContainer[i][j] = s2d->sItems[i].items[j];
            }
        }
        subsetTotal = 0; // reset subsetTotal
    }
    // invoke the displayBestSolutions function to display all solutions starting with the best first
    displayBestSolutions(solutionsContainer, containerSize, numSolutions);

    // de-allocate memory in solutionsContainer
    for (int i = 0; i < subsetSize; i++)
    {
        free(solutionsContainer[i]); // de-allocating columns
    }
    free(solutionsContainer); // de-allocating rows
}