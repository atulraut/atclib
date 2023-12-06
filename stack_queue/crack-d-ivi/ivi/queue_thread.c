/***
        ॐ
        जय भवानी, जय शिवाजी!

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Dec  4 07:12:45 PM PST 2023
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/***** Logic To Test Code *****/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define CAPACITY 10

struct CircularQueue {
    char buffer[CAPACITY];
    int head;
    int tail;
    int size;
    pthread_mutex_t lock;
    pthread_cond_t read_condition;
    pthread_cond_t write_condition;
};

void initQueue(struct CircularQueue *queue) {
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->read_condition, NULL);
    pthread_cond_init(&queue->write_condition, NULL);
}

void write_q(struct CircularQueue *queue, const char *data, int length) {
    pthread_mutex_lock(&queue->lock);

    while (length + queue->size > CAPACITY) {
        pthread_cond_wait(&queue->write_condition, &queue->lock);
    }

    for (int i = 0; i < length; ++i) {
        queue->buffer[queue->tail] = data[i];
        queue->tail = (queue->tail + 1) % CAPACITY;
    }

    queue->size += length;
    pthread_cond_broadcast(&queue->read_condition);

    pthread_mutex_unlock(&queue->lock);
}

void read_q(struct CircularQueue *queue, char *output, int length) {
    pthread_mutex_lock(&queue->lock);

    while (queue->size < length) {
        pthread_cond_wait(&queue->read_condition, &queue->lock);
    }

    for (int i = 0; i < length; ++i) {
        output[i] = queue->buffer[queue->head];
        queue->head = (queue->head + 1) % CAPACITY;
    }

    queue->size -= length;
    pthread_cond_broadcast(&queue->write_condition);

    pthread_mutex_unlock(&queue->lock);
}

void *writerThread(void *arg) {
    struct CircularQueue *queue = (struct CircularQueue *)arg;
    const char data[] = "abcdefghij";
    write_q(queue, data, sizeof(data) - 1);
    debug("Write: %s", data);
    return NULL;
}

void *readerThread(void *arg) {
    struct CircularQueue *queue = (struct CircularQueue *)arg;
    char output[7];
    read_q(queue, output, sizeof(output));
    debug("Read: %.*s", sizeof(output), output);
    return NULL;
}

int main() {
    struct CircularQueue queue;
    initQueue(&queue);

    pthread_t writer, reader;

    pthread_create(&writer, NULL, writerThread, &queue);
    usleep(100000);  // Simulating other work happening concurrently
    pthread_create(&reader, NULL, readerThread, &queue);

    pthread_join(writer, NULL);
    pthread_join(reader, NULL);

    return 0;
}

