#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 8

sem_t mutex;
// This value should only be edited if the mutex is held.
int next_value_to_print = 0;

// Simple function to run in a thread that prints out
// its ID with a number of spaces corresponding to its ID
void *exThreadFunction(void *arg)
{
  int indent = *(int *)arg;

  char* message = malloc(128);
  if (message == NULL) {
    printf("ERROR: could not malloc\n");
    return NULL;
  }
  sprintf(message, "I'm thread %d", indent);
  printf("%*s\n", indent + strlen(message), message);
  // Don't forget to free what we malloc'd
  free(message);
  return NULL;
}

// Simple function to run in a thread that prints out
// its ID with a number of spaces corresponding to its ID.
// Waits until it is this threads turn (based on ID and the
// value of next_value_to_print) to print its ID.
void *exThreadFunctionWithSem(void *arg)
{
  int indent = *(int *)arg;

  char* message = malloc(128);
  if (message == NULL) {
    printf("ERROR: could not malloc\n");
    return NULL;
  }
  // Stay in this loop until we 1) have the mutex and
  // 2) it's this threads turn to print.
  while(1) {
    sleep(1); // try to yield to other threads
    sem_wait(&mutex); // wait for the mutex
    // If it's this threads turn, then print it's ID
    if (next_value_to_print == indent) {
      break;
    }
    // If it's not our time, release the semaphore and keep waiting
    sem_post(&mutex);
  }
  sprintf(message, "i'm thread %d", indent);
  printf("%*s\n", indent + strlen(message), message);
  // NOTE: we must increment the id of the thread whose turn
  // it is to print or the next thread will never exit the
  // while(1) loop;
  next_value_to_print++;
  // Make sure to release the mutex in every code path or your
  // code may lock up
  sem_post(&mutex);

  // Don't forget to free what we malloc'd
  free(message);

  return NULL;
}

void run_8_threads() {
  pthread_t thread_id[NUM_THREADS];
  int args[NUM_THREADS];

  printf("About to spawn threads\n");
  for(int i=0; i<NUM_THREADS; i++) {
    printf("Starting thread %d\n", i);
    args[i] = i;
    pthread_create(&thread_id[i], NULL, exThreadFunction, &args[i]);
  }
  for(int i=0; i<NUM_THREADS; i++) {
    pthread_join(thread_id[i], NULL);
  }
  printf("Threads have joined\n");
}

void run_8_threads_with_sem() {
pthread_t thread_id[NUM_THREADS];
  int args[NUM_THREADS];

  printf("About to spawn threads\n");
  for(int i=0; i<NUM_THREADS; i++) {
    printf("Starting thread %d\n", i);
    args[i] = i;
    pthread_create(&thread_id[i], NULL, exThreadFunctionWithSem, &args[i]);
  }
  for(int i=0; i<NUM_THREADS; i++) {
    pthread_join(thread_id[i], NULL);
  }
  printf("Threads have joined\n");
}

int main()
{
  sem_init(&mutex, 0, 1);

  run_8_threads();
  run_8_threads_with_sem();

  // free the memory allocated by sem_init()
  sem_destroy(&mutex);

  exit(0);
}
