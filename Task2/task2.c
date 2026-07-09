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

void FIFO(int pages[], int n, int frameCount);
void LRU(int pages[], int n, int frameCount);

int main()
{
    int pageSize;
    int frameCount;
    int n;

    printf("Enter Page Size (KB): ");
    scanf("%d", &pageSize);

    printf("Enter Number of Frames: ");
    scanf("%d", &frameCount);

    printf("Enter Number of Page References: ");
    scanf("%d", &n);

    int pages[MAX_PAGES];

    printf("Enter Page Reference String:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("\nMemory Configuration\n");
    printf("--------------------\n");
    printf("Page Size : %d KB\n", pageSize);
    printf("Frames    : %d\n", frameCount);
    printf("References: %d\n", n);

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

// FIFO Page Replacement
void FIFO(int pages[], int n, int frameCount)
{
    printf("\nFIFO Algorithm will be implemented in the next commit.\n");
}

// LRU Page Replacement
void LRU(int pages[], int n, int frameCount)
{
    printf("\nLRU Algorithm will be implemented in the next commit.\n");
}
