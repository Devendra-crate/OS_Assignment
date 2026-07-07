#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_PROCESSES 10

// Shared Counter
int counter = 0;

// Mutex Lock
pthread_mutex_t mutex;

// Semaphore
sem_t semaphore;

// Processes
int processes[NUM_PROCESSES];
int current_process = 0;

int main()
{
    printf("Process Management and Threading\n");

    return 0;
}
