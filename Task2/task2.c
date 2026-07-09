/*
----------------------------------------------------
Task 2: Memory Management Simulation
Course: Operating Systems

Features:
1. Paging System
2. FIFO Page Replacement
3. LRU Page Replacement
4. Page Fault Tracking
5. Hit/Miss Ratio Calculation
----------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Display the current contents of memory frames
void displayFrames(int frames[], int frameCount);

int main()
{
    printf("Memory Management Simulation\n");

    return 0;
}

// Display Memory Frames
void displayFrames(int frames[], int frameCount)
{
    printf("Frames: ");

    for (int i = 0; i < frameCount; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }

    printf("\n");
}
