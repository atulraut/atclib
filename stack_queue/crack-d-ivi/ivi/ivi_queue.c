/**
 * Aim : Queue Implementation for IVI
 * Date : Sat Dec  2 08:35:13 AM PST 2023
 * San Diego, CA
 * By : Atul R. Raut
 * Q->[FIFO] : First In First Out
 * Insert --> Rear++ - Tail++
 * Remove --> Front++ - Head++
 * rear -> front = -1
 Ref: https://www.scaler.com/topics/queue-in-c/
 */
/* -------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct queue_desc {
  int *queue;
  int size;
  int head;
  int tail;
};

/**
   Queue Init - Memory Failure NOT Handled
*/
struct queue_desc *
q_Init(struct queue_desc* obj, const int QSz) {

  obj = (struct queue_desc*)malloc(sizeof(struct queue_desc));
  memset((void *)obj, 0, sizeof(struct queue_desc));
  //  obj->queue = (int *)malloc(sizeof(int) * QSz);
  obj->queue = (int *)calloc(QSz, sizeof(int));
  obj->head = -1;
  obj->tail = -1;
  obj->size = QSz;

  return obj;
}

/**
   Print/Return the Element in the head of the queue
*/
int
Peek(struct queue_desc* qPtr) {

  /* If the queue is empty */
  if (qPtr->head == -1) {
    debug("The Queue doesn't have any Elements!");
    return -1;
  } else {
    /* Printing the element in the head of the queue */
    debug("Head of queue -> [%d] ", qPtr->queue[qPtr->head]);
    return qPtr->queue[qPtr->head];
  }
}

/**
   Check if the queue is empty
*/
bool
isEmpty(struct queue_desc* qPtr) {

  /* If both head and tail are -1 then the queue is empty */
  if (qPtr->head == -1 && qPtr->tail ==-1)
    return true;
  else
    return false;
}

/**
   Check if the queue is full
*/
bool
isFull(struct queue_desc* qPtr) {

  /* If the tail variable is equal to (SIZE - 1) then the queue is full */
  if (qPtr->tail == qPtr->size - 1)
    return true;
  else
    return false;
}

/**
   Get the number of items in the queue
*/
int
q_Size(struct queue_desc* qPtr) {

  /* If the queue is empty, return 0 */
  if(isEmpty(qPtr) == true) {
    return 0;
  }
  /* The number of items in the queue is the difference between head and tail */
  return (qPtr->tail - qPtr->head + 1);
}

/**
   Enqueue or push an element in the queue
*/
void
Enqueue(struct queue_desc* qPtr, int val) {

  /* If the queue is full, return overflow */
  if (isFull(qPtr) == true) {
    debug(" Overflow Condition Encountered! ");
  } else {
    /* If the queue was initally empty
       We add the first element in the queue and update head */
    if (qPtr->head == -1) {
      qPtr->head = 0;
    }

    /* We update the tail pointing to the last element of the queue */
    qPtr->tail++;
    /* Insert the element in the tail position */
    qPtr->queue[qPtr->tail] = val;
    debug("Enque -> [%d] ", val);
  }
}

/**
   Dequeue or pop an element from the queue
*/
int Dequeue(struct queue_desc* qPtr) {
  int val = -1;
  /* If the queue was empty return underflow condition */
  if (isEmpty(qPtr) == true) {
    debug(" Underflow Condition Encountered ");
  } else {   /* Otherwise we pop the element in the head */
    /* Print the popped element */
    val = qPtr->queue[qPtr->head];
    debug(" Dequeue -> [%d] ", qPtr->queue[qPtr->head]);
    /* Increase the index of the head */
    qPtr->head++;
    /* Resetting the queue when the last item is popped from the Queue */
    if (qPtr->head > qPtr->tail) {
      /* Assigning both the head and the tail -1 */
      qPtr->head = qPtr->tail = -1;
    }
  }
  return val;
}

/**
   Print the Queue
*/
void Display(struct queue_desc* qPtr) {

  /* Check If Queue is already Empty */
  if (qPtr->tail == -1) {
    debug("Queue is empty\n");
  } else {
    /* A variable to help in iteration through the queue. */
    int i;
    debug ("Printing the Queue : ");

    /* Printing all the elements of the queue */
    for (i = qPtr->head; i <= qPtr->tail; i++)
      printf("[%s] Element -> [%d] \n", __func__,qPtr->queue[i]);
  }
}

void
test () {
  struct queue_desc *obj, qPtr;
  int QSz = 5;
  obj = q_Init(&qPtr, QSz);

  /* Checking if the queue is empty */
  if (isEmpty(obj))
    printf("The queue is empty\n");

  /* Assigning elements to the queue */
  Enqueue(obj, 4);
  Enqueue(obj, 3);
  Enqueue(obj, 2);
  Enqueue(obj, 1);
  //Enqueue(obj, 5);
  //Enqueue(obj, 6);

  /* Printing the first element of the queue */
  Peek(obj);

  /* Printing the size of the queue */
  printf("[Size] Queue size is -> %d\n", q_Size(obj));

  /* Printing the queue */
  Display(obj);

  /* Popping the elements from the queue */
  Dequeue(obj);
  Dequeue(obj);
  Dequeue(obj);
  Dequeue(obj);
  //Dequeue(obj);
  //Dequeue(obj);
  Enqueue(obj, 5);
  /* Printing the size of the queue */
  printf("[Size] The size of the queue is %d\n", q_Size(obj));

  /* Printing the queue */
  Display(obj);
}

int
main() {
  test ();
  return 0;
}

/**
   >> ./a.out
   The queue is empty
   [Enqueue] L=122 :Enque -> [4]
   [Enqueue] L=122 :Enque -> [3]
   [Enqueue] L=122 :Enque -> [2]
   [Enqueue] L=122 :Enque -> [1]
   [Peek] L=57 :Head of queue -> [4]
   [Size] Queue size is -> 4
   [Display] L=160 :Printing the Queue :
   [Display] Element -> [4]
   [Display] Element -> [3]
   [Display] Element -> [2]
   [Display] Element -> [1]
   [Dequeue] L=137 : Dequeue -> [4]
   [Dequeue] L=137 : Dequeue -> [3]
   [Dequeue] L=137 : Dequeue -> [2]
   [Dequeue] L=137 : Dequeue -> [1]
   [Enqueue] L=122 :Enque -> [5]
   [Size] The size of the queue is 1
   [Display] L=160 :Printing the Queue :
   [Display] Element -> [5]
*/
