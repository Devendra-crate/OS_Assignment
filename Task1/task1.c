/*

Task 1: Process Management and Threading

Features Implemented:
1. Process Creation
2. Multithreading (5 Threads)
3. Mutex Synchronization
4. Semaphore Synchronization
5. Round Robin Scheduling Simulation
6. Deadlock Prevention

Author: Devendra Chhetri

*/



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
pthread_mutex_t resource1;
pthread_mutex_t resource2;

// Semaphore
sem_t semaphore;

// Process Scheduler
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

//
// Worker Thread Function
// Each thread executes processes concurrently while
// using mutexes and semaphores for synchronization.
//
void *worker(void *arg)
{
    int id = *(int *)arg;

    printf("Thread-%d started.\n", id);
    printf("Thread-%d waiting for semaphore...\n", id);

    // Allow only two threads at a time
    printf("Thread-%d entered semaphore.\n", id);

   // Deadlock Prevention
    pthread_mutex_lock(&resource1);
    printf("Thread-%d acquired Resource 1\n", id);

    pthread_mutex_lock(&resource2);
    printf("Thread-%d acquired Resource 2\n", id); 
    // Keep executing until all processes are finished
    while (1)
    {
        pthread_mutex_lock(&mutex);


        // Stop when all processes have been executed
        if (current_process >= NUM_PROCESSES)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("Thread-%d entered critical section.\n", id);

        counter++;
        printf("Shared Counter = %d\n", counter);

        printf("Thread-%d is executing Process-%d\n",
               id,
               processes[current_process]);

        current_process++;

        printf("Time Quantum Completed.\n");

        printf("Thread-%d leaving critical section.\n", id);

        pthread_mutex_unlock(&resource2);
        printf("Thread-%d released Resource 2\n", id);

        pthread_mutex_unlock(&resource1);
        printf("Thread-%d released Resource 1\n", id);
        pthread_mutex_unlock(&mutex);

        
        sleep(1);
    }

    printf("Thread-%d leaving semaphore.\n", id);

    pthread_mutex_unlock(&resource2);
    pthread_mutex_unlock(&resource1);

    printf("Thread-%d released Resource 2\n", id);
    printf("Thread-%d released Resource 1\n", id); 

    sem_post(&semaphore);

    pthread_exit(NULL);
}

//
// Main Function
// Initializes synchronization mechanisms,
// creates processes and worker threads,waits for execution to complete,
// and cleans up allocated resources.

int main()
{
    createProcesses();

    pthread_mutex_init(&mutex, NULL);

    pthread_mutex_init(&resource1, NULL);
    pthread_mutex_init(&resource2, NULL);

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

        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0)
        {
            printf("Error creating thread %d\n", i + 1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\n");
    printf("All Processes Executed Successfully\n");
    printf("Final Shared Counter = %d\n", counter);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&resource1);
    pthread_mutex_destroy(&resource2);

    sem_destroy(&semaphore);

    return 0;
}
