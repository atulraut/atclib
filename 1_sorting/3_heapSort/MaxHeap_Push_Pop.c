/***
    By TechDose
    Max Heap Implementation | Push | Pop | CODE

    https://techdose.co.in/heap-implementation-push-pop-code/

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Dec 31 13:09:19 PST 2022
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

//Max_Heap implementation

enum heap_s {
  PUSH = 1,
  POP = 2,
  SHOW = 3,
};

#define MAX_HEAP_SIZE 1001

struct heap {
  int* buf;
  int heapSize;
};

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
// Time - O(logN)
// Space- O(1)
// Insert Top-Down & Left-To-Right
/***
    Algo :
    1] Check for Overflow - O(1)
    2] Incrase HeapSize   - O(1)
    3] Insert New Element at Last - O(1)
    4] Apply Percolate-Up Algo - O(logN)
    Time - O(logN)
    Space- O(1)
 */
void heap_push(struct heap *thisHeap, int val) {
  if(thisHeap->heapSize >= MAX_HEAP_SIZE) {
    debug("Overflow Returning!");
    return;
  }

  thisHeap->buf[thisHeap->heapSize] = val;    //Push 1st element to the end of heap
  int curr = thisHeap->heapSize;
  //percolate-up - heapify, making sure current value if less than root goes to left else right.
  while(curr>0 && thisHeap->buf[(curr-1)/2] < thisHeap->buf[curr]) {
    swap(thisHeap->buf+(curr-1)/2, thisHeap->buf+curr);

    curr = (curr-1)/2;    //Current pointer moves to parent
  }
  thisHeap->heapSize += 1; // Add new element, so increase heap size
}
// Same as extract max/min
// User Percolate-down algo here
// stopping at if only have/reach leaf node RO
// Root is > both left & right child.
/***
    Algo:
    1] Check for Underflow - O(1)
    2] Save the Root Element - O(1)
    3] Copy last element to the root - O(1)
    4] Decrease HeapSize - O(1)
    5] Max/Min Heapify - O(logN)
    Time - O(logN)
    Space- O(logN)
 */
int heap_pop(struct heap *thisHeap) {
  if(thisHeap->heapSize <= 0) {
    debug("Underflow Returning!");
    return -1;
  }

  int curr = 0;    //Current index is 0 which is root (storing max element)
  int popped = thisHeap->buf[0];    //Save the element to be popped
  thisHeap->buf[0] = thisHeap->buf[thisHeap->heapSize-1];    //Copy last element to the root
  thisHeap->heapSize -= 1;    //Reduce heapsize by 1

  //Max_heapify
  while((2*curr+1) < thisHeap->heapSize) {  //While we don't reach a leaf node

    int child;
    if((2*curr+2) == thisHeap->heapSize)    //If we only have leftchild
      child = 2*curr+1;
    else {   //If both left and right child are present then find which is maximum
      if(thisHeap->buf[2*curr+1] > thisHeap->buf[2*curr+2])
	child = 2*curr+1; // left child
      else
	child = 2*curr+2; // right child
    }

    //If curr node is lower than max(leftChild,rightChild) then swap and do max_heapify again for that child
    if(thisHeap->buf[curr] < thisHeap->buf[child]) {
      swap(thisHeap->buf+curr, thisHeap->buf+child);

      curr = child;
    }
    else    //Max heapify is done (because the curr node is having higher value than both lchild and rchild)
      break;
  }
  return popped;
}

void show_heap(struct heap *thisHeap) {
  for(int i=0; i<thisHeap->heapSize; ++i)
    debug("->[%d]", thisHeap->buf[i]);
  printf("\n");
}

struct heap* init(int sz) {
  struct heap *thisHeap = (struct heap*)malloc(sizeof(struct heap));
  thisHeap->buf = (int *)malloc(sizeof(int) * sz);
  thisHeap->heapSize = sz;
  return thisHeap;
}

void test() {
  int ret = 0;
  int sz = 3;
  struct heap* thisHeap = init(sz);

  while(1) {
    debug("1:Push...2:Pop...3:Show_Heap...4:Terminate\n");
    int option;
    int element;
    scanf("%d", &option);

    switch(option) {
      case PUSH:
	debug("Enter element!");
	scanf("%d", &element);
	heap_push(thisHeap, element);
	break;
      case POP:
	debug("Popped =%d", heap_pop(thisHeap));
	break;
      case SHOW:
	show_heap(thisHeap);
	break;
      default:
	return;
      }
  }
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
/*
  => ./a.out
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  1
  [test] L=132 :Enter element!
  10
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  1
  [test] L=132 :Enter element!
  20
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  1
  [test] L=132 :Enter element!
  30
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  1
  [test] L=132 :Enter element!
  40
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  3
  [show_heap] L=109 :->[40]
  [show_heap] L=109 :->[30]
  [show_heap] L=109 :->[20]
  [show_heap] L=109 :->[10]

  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  2
  [test] L=137 :Popped =40
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  2
  [test] L=137 :Popped =30
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  2
  [test] L=137 :Popped =20
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  2
  [test] L=137 :Popped =10
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  2
  [heap_pop] L=73 :Underflow Returning!
  [test] L=137 :Popped =-1
  [test] L=125 :1:Push...2:Pop...3:Show_Heap...4:Terminate

  4
*/
