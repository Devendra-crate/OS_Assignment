/*
----------------------------------------------------
Task 2: Memory Management Simulation

Features Implemented:
1. Paging System with Configurable Page Size
2. FIFO Page Replacement Algorithm
3. LRU Page Replacement Algorithm
4. Page Fault and Page Hit Tracking
5. Hit/Miss Ratio Calculation
6. Memory Frame Visualization

Author: Devendra Chhetri
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

    printf("\n");
    printf("FIFO Page Replacement Simulation\n");
    printf("\n");

    FIFO(pages, n, frameCount);

    printf("\n");
    printf("LRU Page Replacement Simulation\n");

    LRU(pages, n, frameCount);

    printf("\n");
    printf("Memory Management Simulation Completed Successfully\n");
    
    return 0;
}

// Display Memory Frames
// Shows the current allocation of pages in memory.
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


// FIFO Page Replacement Algorithm
// Replaces the oldest page currently in memory.

void FIFO(int pages[], int n, int frameCount)
{
    int frames[MAX_FRAMES];
    int faults = 0;
    int hits = 0;
    int index = 0;
   
    // Initialize all memory frames as empty

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\n========== FIFO ==========\n");
   
   // Process each page reference
    for (int i = 0; i < n; i++)
    {
        int found = 0;

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                hits++;
                break;
            }
        }

      // Process each page reference
        if (!found)
        {
            frames[index] = pages[i];
            index = (index + 1) % frameCount;
            faults++;
        }

        printf("\nProcessing Page %d\n", pages[i]);
        printf("Memory Status -> ");
        displayFrames(frames, frameCount);
    }

    printf("\nFIFO Summary\n");
    printf("--------------------\n");
    printf("Total Page References : %d\n", n);
    printf("Page Faults           : %d\n", faults);
    printf("Page Hits             : %d\n", hits);

    float hitRatio = (float)hits / n;
    float missRatio = (float)faults / n;

    printf("Hit Ratio             : %.2f\n", hitRatio);
    printf("Miss Ratio            : %.2f\n", missRatio);
}

//LRU Page Replacement Algorithm
//Replaces the least recently used page.

void LRU(int pages[], int n, int frameCount)
{
    int frames[MAX_FRAMES];
    int recent[MAX_FRAMES];

    int faults = 0;
    int hits = 0;

    // Initialize memory frames and usage history
    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\n========== LRU ==========\n");

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                hits++;
                recent[j] = i;
                break;
            }
        }

       // Find an empty frame or replace the least recently used page
        if (!found)
        {
            int empty = -1;

            for (int j = 0; j < frameCount; j++)
            {
                if (frames[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
            {
                frames[empty] = pages[i];
                recent[empty] = i;
            }
            else
            {
                int lru = 0;

                for (int j = 1; j < frameCount; j++)
                {
                    if (recent[j] < recent[lru])
                        lru = j;
                }

                frames[lru] = pages[i];
                recent[lru] = i;
            }

            faults++;
        }

        printf("\nProcessing Page %d\n", pages[i]);
        printf("Memory Status -> ");
        displayFrames(frames, frameCount);
    }

    printf("\nLRU Summary\n");
    printf("--------------------\n");
    printf("Total Page References : %d\n", n);
    printf("Page Faults           : %d\n", faults);
    printf("Page Hits             : %d\n", hits);

   float hitRatio = (float)hits / n;
   float missRatio = (float)faults / n;

   printf("Hit Ratio             : %.2f\n", hitRatio);
   printf("Miss Ratio            : %.2f\n", missRatio);
}
