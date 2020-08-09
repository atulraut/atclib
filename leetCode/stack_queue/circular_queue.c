/***
 * https://leetcode.com/problems/design-circular-queue/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
  int data;
  struct Node *next;
}Node;

typedef struct {
  Node *front;//From the front when decreasing
  Node *rear;//From the back when adding
  int size;
  int count;
} MyCircularQueue;

/** Initialize your data structure here. Set the size of the queue to be k. */

MyCircularQueue* myCircularQueueCreate(int k) {
  MyCircularQueue *obj=(MyCircularQueue*)malloc(sizeof(MyCircularQueue));
  obj->rear=NULL;
  obj->front=NULL;
  obj->size=k;
  obj->count=0;
  return obj;
}

/** Checks whether the circular queue is empty or not. */
int myCircularQueueIsEmpty(MyCircularQueue* obj) {
  if(obj->count==0)
    return 1;
  else
    return -1;
}

/** Checks whether the circular queue is full or not. */
int myCircularQueueIsFull1(MyCircularQueue* obj) {
  if(obj->size==obj->count)
    return 1;
  else
    return -1;
}

/** Insert an element into the circular queue. Return true if the operation is successful. */
int myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
  if(obj -> size == obj -> count){
    return -1;
  } else{
    if(obj->front == NULL){
      Node *en = (Node*)malloc(sizeof(Node));//define en
      en -> next = NULL;
      en -> data = value;
      obj -> front = en;//There is only one node en
      obj->rear = en; //rear and front at the same time
      (obj->count)++;//Each additional node increases a count
      //obj -> front = obj -> front -> next;
    }
    else{
      Node *en = (Node*)malloc(sizeof(Node));//define en
      en -> next = NULL;
      en -> data = value;
      obj -> rear->next = en;//The last one is en
      obj -> rear = obj -> rear -> next;
      //obj->rear->next;//Move the rear of obj to the next of rear, which is the last one
      (obj->count)++;//Each additional node increases a count
    }
  }
  return 1;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
int myCircularQueueDeQueue(MyCircularQueue* obj) {
  if (obj -> count == 0){//When obj is empty
    return -1;
  }
  else{
    if(obj -> count == 1){//When there is only one obj
      Node *temp = (Node*)malloc(sizeof(Node));//Create a temp ready to free
      temp = obj->front;//temp is set to the front of obj
      free(temp);//free off temp
      obj->front = NULL;
      obj->rear = NULL;
      (obj->count)--;//Every reduction of a node will reduce a count
    }
    else{
      Node *temp = (Node*)malloc(sizeof(Node));//The temp is ready to be free
      temp = obj -> front;//Turn temp into the front of obj
      obj -> front = obj -> front -> next;//Turn the original first into temp
      free(temp);
      (obj->count)--;//Every reduction of a node will reduce a count
    }
  }
  return 1;
}

/** Get the front item from the queue. */
int myCircularQueueFront(MyCircularQueue* obj) {
  if(obj->front==NULL){
    return -1;
  } else
    return obj->front->data;
}

/** Get the last item from the queue. */
int myCircularQueueRear(MyCircularQueue* obj) {
  if(obj->rear==NULL){
    return -1;
  }
  else return obj->rear->data;
}

void myCircularQueueFree(MyCircularQueue* obj) {
  free (obj);
}
/*
void m_display (void *_ptr) {
  int i;
  MyCircularQueue *q = (MyCircularQueue *)_ptr;
  printf ("[m_display] Inside q->front=%d q->rear=%d\n", q->front, q->rear);
  for (i=q->front; i<=q->rear; i++) {
    printf ("[m_display] = [%d]\n", q->buf[i]);
  }
}
*/
/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 
/ * bool param_2 = myCircularQueueDeQueue(obj);
 
 * int param_3 = myCircularQueueFront(obj);
 
 * int param_4 = myCircularQueueRear(obj);
 
 * bool param_5 = myCircularQueueIsEmpty(obj);
 
 * bool param_6 = myCircularQueueIsFull(obj);
 
 * mng0yCircularQueueFree(obj);
 */

int main () {
 MyCircularQueue* obj = myCircularQueueCreate(5);

 for (int i=1; i<=5; i++) 
   myCircularQueueEnQueue(obj, i*10);

 // printf ("Enque param  = %d =%d \n", param_0, param_1);
 
 int param_2 = myCircularQueueDeQueue(obj);
 printf ("Deque param = %d \n", param_2);
 
 int param_3 = myCircularQueueFront(obj);
 printf ("QFront param = %d \n", param_3);
 
 int param_4 = myCircularQueueRear(obj);
 printf ("QRear param = %d \n", param_4);
 
 int param_5 = myCircularQueueIsEmpty(obj);
 printf ("IsEmpty param = %d \n", param_5);
 
 int param_6 = myCircularQueueIsFull(obj);

 //m_display (obj);
 printf ("param = %d \n", param_6);
 
 myCircularQueueFree(obj);
}
