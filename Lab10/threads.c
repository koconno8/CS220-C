#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global_var = 100;

void *worker_function(void *payload){
  global_var --;
  (*(int*) payload)++;
  printf("global_var = %d, payload = %d\n", global_var, *(int*) payload);
}

#define NUM_THREADS 3

int main() {
  pthread_t threads [NUM_THREADS];
  int i;

  int * payload = (int *) malloc(sizeof(int));
  *payload = 800;

  for (i = 0; i < NUM_THREADS; i++){
    pthread_create(&threads[i], NULL, worker_function, (void *) payload);
  }

  printf("In main thread\n");

  for(i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
  }

  printf("Exiting main thread\n");
  pthread_exit(NULL);
  return 0;
}
