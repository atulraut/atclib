/***
    https://leetcode.com/explore/learn/card/queue-stack/228/first-in-first-out-data-structure/1396/

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sun Sep 10 03:00:47 PM PDT 2023
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

struct queue {
  int* buf;
  int head;
  int tail;
  int size;
};

/** Initialize your data structure here. Set the size of the queue to be k. */
struct queue* MyCircularQueue(int k) {
  struct queue* thisQ= (struct queue *)malloc(sizeof(struct queue));
  thisQ->buf = (int *)malloc(sizeof(int) * k);
  thisQ->head = -1;
  thisQ->tail = -1;
  thisQ->size = k;
  return thisQ;
}

/** Checks whether the circular queue is empty or not. */
bool isEmpty(struct queue* thisQ) {
  return (thisQ->head == -1);
}

/** Checks whether the circular queue is full or not. */
bool isFull(struct queue* thisQ) {
  return ((thisQ->tail + 1) % thisQ->size) == thisQ->head;
}

/** Insert an element into the circular queue. Return true if the operation is successful. */
bool enQueue(struct queue* thisQ, int value) {
  if (isFull(thisQ)) {
    return false;
  }
  if (isEmpty(thisQ)) {
    thisQ->head = 0;
  }

  thisQ->tail = (thisQ->tail + 1) % thisQ->size;
  thisQ->buf[thisQ->tail] = value;
  return true;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool deQueue(struct queue* thisQ) {
  if (isEmpty(thisQ)) {
    return false;
  }
  if (thisQ->head == thisQ->tail) {
    thisQ->head = -1;
    thisQ->tail = -1;
    return true;
  }
  thisQ->head = (thisQ->head + 1) % thisQ->size;
  return true;
}

/** Get the front item from the queue. */
int Front(struct queue* thisQ) {
  if (isEmpty(thisQ)) {
    return -1;
  }
  return thisQ->buf[thisQ->head];
}

/** Get the last item from the queue. */
int Rear(struct queue* thisQ) {
  if (isEmpty(thisQ)) {
    return -1;
  }
  return thisQ->buf[thisQ->tail];
}

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue obj = new MyCircularQueue(k);
 * bool param_1 = obj.enQueue(value);
 * bool param_2 = obj.deQueue();
 * int param_3 = obj.Front();
 * int param_4 = obj.Rear();
 * bool param_5 = obj.isEmpty();
 * bool param_6 = obj.isFull();
 */

void test () {
  int k = 5;
  struct queue* QObj =   MyCircularQueue(k);
  for (int i=1; i<=k; ++i)
    debug("enQueue-> [%d]", enQueue(QObj, 5*i));

  bool param_2 = deQueue(QObj);
  debug ("param_2 = %d", param_2);
  int param_3 = Front(QObj);
  debug ("param_3= %d", param_3);
  int param_4 = Rear(QObj);
  debug ("param_4= %d", param_4);
  bool param_5 = isEmpty(QObj);
  debug ("param_5= %d", param_5);
  bool param_6 = isFull(QObj);
  debug ("param_6= %d", param_6);
}

int main () {
  test ();
}
