/**

   Thread-safe FIFO queue in C

    Queue Basics :

    Q->[FIFO] : First In First Out

    Q --> IR++ RF++
	Insert --> Tail++ | Rear++  {Key:: ITR}
	Remove --> Head++ | Front++

	Insert --> if (rear == MAX-1) --> Overflow
	Remove --> if (front > rear)  --> Underflow

      [Remove]
       Head
	-------------------------------------------------
	|    2	|   3	|   5	|   6	|   7	|   8	|
	-------------------------------------------------
	0	1	2	3	4	5
							Tail[Insert]

   Date : Sun Sep 27 21:53:30 PDT 2026
   Folsom, CA.
 **/
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define FIFO_SIZE 8

typedef struct {
  int buffer[FIFO_SIZE];

  int head;       // next position to read
  int tail;       // next position to write
  int count;      // number of elements currently stored

  pthread_mutex_t lock;

  pthread_cond_t not_empty;
  pthread_cond_t not_full;
} fifo_t;

/*
 * Initialize FIFO
 */
int fifo_init(fifo_t *q) {
  if (q == NULL)
    return -1;

  q->head = 0;
  q->tail = 0;
  q->count = 0;

  if (pthread_mutex_init(&q->lock, NULL) != 0)
    return -1;

  if (pthread_cond_init(&q->not_empty, NULL) != 0) {
    pthread_mutex_destroy(&q->lock);
    return -1;
  }

  if (pthread_cond_init(&q->not_full, NULL) != 0) {
    pthread_cond_destroy(&q->not_empty);
    pthread_mutex_destroy(&q->lock);
    return -1;
  }
  return 0;
}

/*
 * Blocking PUSH
 *
 * If FIFO is full, producer sleeps until
 * a consumer removes something.
 */
int fifo_push(fifo_t *q, int value) {
  if (q == NULL)
    return -1;

  pthread_mutex_lock(&q->lock);

  /*
   * Wait while FIFO is full.
   *
   * Use while instead of if because:
   *   - spurious wakeups are possible
   *   - another producer may get the lock first
   */
  while (q->count == FIFO_SIZE)
    pthread_cond_wait(&q->not_full, &q->lock);

  /*
   * Insert element.
   */
  q->buffer[q->tail] = value;
  q->tail = (q->tail + 1) % FIFO_SIZE;
  q->count++;

  /*
   * Data is available now.
   * Wake one waiting consumer.
   */
  pthread_cond_signal(&q->not_empty);
  pthread_mutex_unlock(&q->lock);

  return 0;
}

/*
 * Blocking POP
 *
 * If FIFO is empty, consumer sleeps until
 * a producer inserts something.
 */
int fifo_pop(fifo_t *q, int *value) {
  if (q == NULL || value == NULL)
    return -1;

  pthread_mutex_lock(&q->lock);

  /*
   * Wait while FIFO is empty.
   */
  while (q->count == 0)
    pthread_cond_wait(&q->not_empty, &q->lock);

  /*
   * Read element.
   */
  *value = q->buffer[q->head];
  q->head = (q->head + 1) % FIFO_SIZE;
  q->count--;

  /*
   * Space is available now.
   * Wake one waiting producer.
   */
  pthread_cond_signal(&q->not_full);
  pthread_mutex_unlock(&q->lock);

  return 0;
}

/*
 * Non-blocking PUSH
 *
 * Returns:
 *   true  -> success
 *   false -> FIFO full
 */
bool fifo_try_push(fifo_t *q, int value) {
  if (q == NULL)
    return false;

  pthread_mutex_lock(&q->lock);

  if (q->count == FIFO_SIZE) {
    pthread_mutex_unlock(&q->lock);
    return false;
  }

  q->buffer[q->tail] = value;
  q->tail = (q->tail + 1) % FIFO_SIZE;
  q->count++;

  pthread_cond_signal(&q->not_empty);
  pthread_mutex_unlock(&q->lock);

  return true;
}

/*
 * Non-blocking POP
 *
 * Returns:
 *   true  -> success
 *   false -> FIFO empty
 */
bool fifo_try_pop(fifo_t *q, int *value) {
  if (q == NULL || value == NULL)
    return false;

  pthread_mutex_lock(&q->lock);

  if (q->count == 0) {
    pthread_mutex_unlock(&q->lock);
    return false;
  }

  *value = q->buffer[q->head];
  q->head = (q->head + 1) % FIFO_SIZE;
  q->count--;

  pthread_cond_signal(&q->not_full);
  pthread_mutex_unlock(&q->lock);

  return true;
}

/*
 * Destroy FIFO
 *
 * Caller must make sure no threads are
 * currently using the FIFO.
 */
void fifo_destroy(fifo_t *q) {
  if (q == NULL)
    return;

  pthread_mutex_destroy(&q->lock);
  pthread_cond_destroy(&q->not_empty);
  pthread_cond_destroy(&q->not_full);
}

void *producer(void *arg) {
  int id = *(int *)arg;

  for (int i = 0; i < 10; i++) {

    int value = id * 100 + i;

    fifo_push(&fifo, value);

    printf("Producer %d -> %d\n", id, value);

    usleep(100000);
  }

  return NULL;
}


void *consumer(void *arg) {
  int id = *(int *)arg;

  for (int i = 0; i < 10; i++) {

    int value;

    fifo_pop(&fifo, &value);

    printf("Consumer %d <- %d\n", id, value);

    usleep(200000);
  }
  return NULL;
}

fifo_t fifo;

int main(void) {
  pthread_t p1, p2;
  pthread_t c1, c2;

  int p1_id = 1;
  int p2_id = 2;
  int c1_id = 1;
  int c2_id = 2;

  fifo_init(&fifo);

  pthread_create(&p1, NULL, producer, &p1_id);
  pthread_create(&p2, NULL, producer, &p2_id);

  pthread_create(&c1, NULL, consumer, &c1_id);
  pthread_create(&c2, NULL, consumer, &c2_id);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  pthread_join(c1, NULL);
  pthread_join(c2, NULL);

  fifo_destroy(&fifo);

  return 0;
}

/**
   Producer 1 -> 100
   Consumer 2 <- 200
   Consumer 1 <- 100
   Producer 2 -> 200
   Producer 1 -> 101
   Producer 2 -> 201
   Consumer 1 <- 101
   Consumer 2 <- 201
   Producer 1 -> 102
   Producer 2 -> 202
   Producer 1 -> 103
   Producer 2 -> 203
   Consumer 1 <- 102
   Consumer 2 <- 202
   Producer 1 -> 104
   Producer 2 -> 204
   Producer 1 -> 105
   Producer 2 -> 205
   Consumer 2 <- 103
   Consumer 1 <- 203
   Producer 1 -> 106
   Producer 2 -> 206
   Producer 1 -> 107
   Producer 2 -> 207
   Consumer 2 <- 104
   Consumer 1 <- 204
   Producer 1 -> 108
   Producer 2 -> 208
   Consumer 2 <- 105
   Producer 1 -> 109
   Consumer 1 <- 205
   Producer 2 -> 209
   Consumer 2 <- 106
   Consumer 1 <- 206
   Consumer 2 <- 107
   Consumer 1 <- 207
   Consumer 2 <- 108
   Consumer 1 <- 208
   Consumer 2 <- 109
   Consumer 1 <- 209
**/

