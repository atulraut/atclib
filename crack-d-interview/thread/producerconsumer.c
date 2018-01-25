/*
 *  Solution to Producer Consumer Problem Using Pthreads, a mutex and condition variables
 *  From Tanenbaum, Modern Operating Systems, 3rd Ed. In this version the buffer is a single number.
 *  The producer is putting numbers into the shared buffer (in this case sequentially)
 *  And the consumer is taking them out. If the buffer contains zero, that indicates that the buffer is empty.
 *  Any other value is valid.
 *  To Compile =-->    g++ producerconsumerpthread.c  -o main.out -pthread -std=c++11
*/

#include <stdio.h>
#include <pthread.h>

#define MAX 10              /* FIFO buffer size, Numbers to produce */
pthread_mutex_t the_mutex;  /* init the_mutext to resource size to manage resource, we have 0*/
pthread_cond_t condc;       /* stall current process if (the_mutex <=0 else the_mutex -=1) */
pthread_cond_t condp;       /* the+mutex +=1 let other process to proceed */
int buffer = 0;             /*FIFO buffer e.g. char buf[MAX]*/

void* producer(void *ptr) {
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex); /* protect buffer */
    while (buffer != 0)             /* If there is something in the buffer then wait */
      pthread_cond_wait(&condp, &the_mutex); /* Before enter critical section Hold lock so only 1 process can access critical section */
    buffer = i;
    printf ("2. producer: buffer = %d \n", buffer);
    pthread_cond_signal(&condc);         /*3. wake up consumer, Finished with lock */
    pthread_mutex_unlock(&the_mutex);    /* release the buffer */
  }
  pthread_exit(0);
}

void* consumer(void *ptr) {
  int i;

  for (i = 1; i <= MAX; i++) {
    pthread_mutex_lock(&the_mutex);/* protect buffer */
    while (buffer == 0)/* 1. If there is nothing in 
			  the buffer then wait */
    pthread_cond_wait(&condc, &the_mutex); /* Before enter critical section Hold lock so only 1 process can access critical section */
    printf ("4. consumer: buffer = %d \n", buffer);
    buffer = 0;    
    pthread_cond_signal(&condp);/*5. wake up producer, Finished with lock */
    pthread_mutex_unlock(&the_mutex);/* release the buffer */
  }
  pthread_exit(0);
}

int main(int argc, char **argv) {
  pthread_t pro, con;

  // Initialize the mutex and condition variables
  /* What's the NULL for ??? */
  pthread_mutex_init(&the_mutex, NULL);
  pthread_cond_init(&condc, NULL);/* Initialize consumer condition variable */
  pthread_cond_init(&condp, NULL);/* Initialize producer condition variable */

  // Create the threads
  pthread_create(&con, NULL, consumer, NULL);
  pthread_create(&pro, NULL, producer, NULL);

  // Wait for the threads to finish
  // Otherwise main might run to the end
  // and kill the entire process when it exits.
  pthread_join(con, NULL);
  pthread_join(pro, NULL);

  // Cleanup -- would happen automatically at end of program
  pthread_mutex_destroy(&the_mutex);/* Free up the_mutex */
  pthread_cond_destroy(&condc);/* Free up consumer condition variable */
  pthread_cond_destroy(&condp);/* Free up producer condition variable */
}
