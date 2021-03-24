/***
    Ref : https://www.linuxquestions.org/questions/programming-9/efficient-message-queue-for-communication-between-threads-938703/

    Implement a thread-safe queue component using basic synchronization
    primitives. A put() method (which can be called from multiple
    producer threads) adds a message to the queue. A get() method
    (called from a single consumer thread) returns the next available
    message in the queue, blocking while the queue is empty.

    Date : 24 March 2021
    San Diego, CA.

    gcc msg_queue.c -o main.out -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct job {
  int data;
}; /* Up to you */

pthread_mutex_t the_mutex;
pthread_cond_t condc;       /* stall current process if (the_mutex <=0 else the_mutex -=1) */
pthread_cond_t condp;       /* the+mutex +=1 let other process to proceed */

struct queue {
  pthread_mutex_t   lock;
  pthread_cond_t    wait_room;
  pthread_cond_t    wait_data;
  unsigned int      size;
  unsigned int      head;   // FRONT
  unsigned int      tail; // REAR
  struct job      **queue;
};

int queue_init(struct queue *const q, const unsigned int slots) {
  int errno;
  if (!q || slots < 1U)
    return errno = EINVAL;

  q->queue =  (struct job **)malloc(sizeof (struct job *) * (size_t)(slots + 1));
  if (!q->queue)
    return errno = ENOMEM;

  q->size = slots + 1U;
  q->head = 0U;
  q->tail = 0U;

  pthread_mutex_init(&q->lock, NULL);
  pthread_cond_init(&q->wait_room, NULL);
  pthread_cond_init(&q->wait_data, NULL);

  return 0;
}

/***
   Consumer : Remove
   A get() method called from a single consumer thread
   returns the next available message in the queue, blocking
   while the queue is empty.
*/
struct job *queue_get(struct queue *const q) {
  struct job *j;
  printf ("[%s] L=%d: Enter \n",  __func__, __LINE__);

  pthread_mutex_lock(&q->lock);
  while (q->head == q->tail) {
    printf ("[%s] L=%d: Waiting for Data! \n",  __func__, __LINE__);
    pthread_cond_wait(&q->wait_data, &q->lock);
  }
  printf ("[%s] L=%d: Enter to get Data! tail=%d\n",  __func__, __LINE__, q->tail);
  j = q->queue[q->tail+1];
  if(j)
    printf ("[%s] L=%d: Reached! head = %d q->tail=%d data = %d\n",  __func__, __LINE__, q->head, q->tail, j->data);

  q->queue[q->tail] = NULL;
  q->tail = (q->tail + 1U) % q->size;

  pthread_cond_signal(&q->wait_room);

  pthread_mutex_unlock(&q->lock);

  //int data = *((int *)(j->data));
  if (j != NULL)
    printf ("[%s] L=%d: Consumer Got Data = %d \n",  __func__, __LINE__, j->data);
  return j;
}

/***
   Producer : Insertion
   A put() method (which can be called from multiple
   producer threads) adds a message to the queue.
   */
void queue_put(struct queue *const q, struct job *const j) {
  printf ("[%s] L=%d: Enter \n",  __func__, __LINE__);
  pthread_mutex_lock(&q->lock);
  while ((q->head + 1U) % q->size == q->tail)
    pthread_cond_wait(&q->wait_room, &q->lock);

  q->head = (q->head + 1U) % q->size;

  q->queue[q->head] = j;

  pthread_cond_signal(&q->wait_data);

  pthread_mutex_unlock(&q->lock);
  printf ("[%s] L=%d: End head = %d q->tail=%d data = %d\n",  __func__, __LINE__, q->head, q->tail, j->data);
  return;
}

void* producer(void *ptr) {
  printf ("[%s] L=%d: Enter \n",  __func__, __LINE__);
  struct queue *q = (struct queue*)ptr;
  struct job *j;
  static int i = 10;
  ++i;
  j = (struct job *)malloc(sizeof(int) * 1);
  j->data = i;
  printf ("[%s] L=%d: adding data = %d \n",  __func__, __LINE__, i);
  queue_put(q, j);
}

void* consumer(void *ptr) {
  printf ("[%s] L=%d: Enter \n",  __func__, __LINE__);
  struct queue *q = (struct queue*)ptr;
  struct job *j = queue_get(q);
  printf ("[%s] L=%d: Reached! \n",  __func__, __LINE__);
  //int *i = j->data;
  printf ("[%s] L=%d: Reached! \n",  __func__, __LINE__);
  if (j != NULL)
    printf ("[%s] L=%d: j->data = %d \n",  __func__, __LINE__, (j->data));
}

int main(int argc, char **argv) {
  int ret;
  int tsz = 3;
  struct queue q;
  pthread_t pro[tsz];
  pthread_t con[tsz];

  unsigned int slots = 10;
  ret = queue_init(&q, slots);

  pthread_cond_init(&condc, NULL);/* Initialize consumer condition variable */
  pthread_cond_init(&condp, NULL);/* Initialize producer condition variable */


  //
  // Create the threads
  for (int i = 0; i<tsz; i++) {
    pthread_create(&con[i], NULL, consumer, (void *)&q);
    pthread_create(&pro[i], NULL, producer, (void *)&q);
  }
  // Wait for the threads to finish
  // Otherwise main might run to the end
  // and kill the entire process when it exits.
  for (int i = 0; i<tsz; i++) {
    pthread_join(con[i], NULL);
    pthread_join(pro[i], NULL);
  }

  pthread_mutex_destroy(&q.lock);/* Free up the_mutex */
  pthread_cond_destroy(&q.wait_data);/* Free up consumer condition variable */
  pthread_cond_destroy(&q.wait_room);/* Free up producer condition variable */

  return 0;
}
