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

// Initialize Processes
void createProcesses()
{
    for(int i=0;i<NUM_PROCESSES;i++)
    {
        processes[i]=i+1;
    }
}

// Worker Thread Function
void *worker(void *arg)
{
    int id = *(int *)arg;

    printf("Thread-%d started.\n", id);

    printf("Thread-%d waiting for semaphore...\n", id);

    // Acquire semaphore
    sem_wait(&semaphore);

    printf("Thread-%d entered semaphore.\n", id);

    // Lock mutex
    pthread_mutex_lock(&mutex);

    printf("Thread-%d entered critical section.\n", id);

    counter++;

    printf("Counter = %d\n", counter);

    sleep(1);

    printf("Thread-%d leaving critical section.\n", id);

    // Unlock mutex
    pthread_mutex_unlock(&mutex);

    printf("Thread-%d leaving semaphore.\n", id);

    // Release semaphore
    sem_post(&semaphore);

    pthread_exit(NULL);
}


int main()
{
    createProcesses();

    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaphore, 0, 2);

    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    printf("Process Management and Threading\n\n");

    printf("Processes Created:\n");

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        printf("Process-%d\n", processes[i]);
    }

    printf("\nCreating Threads...\n");

    for (int i = 0; i < NUM_THREADS; i++)
    {
        ids[i] = i + 1;

        pthread_create(&threads[i],
                       NULL,
                       worker,
                       &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);

    return 0;
}
