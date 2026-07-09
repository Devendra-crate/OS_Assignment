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

    FIFO(pages, n, frameCount);
    LRU(pages, n, frameCount);

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

// ------------------- FIFO -------------------
void FIFO(int pages[], int n, int frameCount)
{
    int frames[MAX_FRAMES];
    int faults = 0;
    int hits = 0;
    int index = 0;

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\n========== FIFO ==========\n");

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

        if (!found)
        {
            frames[index] = pages[i];
            index = (index + 1) % frameCount;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        displayFrames(frames, frameCount);
    }

    printf("\nPage Faults = %d\n", faults);
    printf("Page Hits = %d\n", hits);
}

// ------------------- LRU -------------------
void LRU(int pages[], int n, int frameCount)
{
    int frames[MAX_FRAMES];
    int recent[MAX_FRAMES];

    int faults = 0;
    int hits = 0;

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

        printf("Page %d -> ", pages[i]);
        displayFrames(frames, frameCount);
    }

    printf("\nPage Faults = %d\n", faults);
    printf("Page Hits = %d\n", hits);
}
