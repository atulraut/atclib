/***
    Heap Sort :

    Ref :
    https://techdose.co.in/heapsort-algorithm-code-implementation/
    https://www.youtube.com/watch?v=kU4KBD4NFtw

    RELATED LINKS:
    Power of Heap: https://youtu.be/RU08pp_VPSs
    Concepts of Heap: https://youtu.be/N0Frqx9UlrI
    Representation of Heap: https://youtu.be/qQkfUKer3LU
    Heapify Algorithm: https://youtu.be/cuL8gXCSA58
    Build heap algorithm: https://youtu.be/VkKmmwzfIG4
    Heap Algorithm: https://youtu.be/KkeIB6soiVI

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Sep  2 06:36:58 PM PDT 2022
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/
void display_this(int* heap, int sz) {
  debug ("Size of array = %d", sz);
  for (int i=0; i<sz; ++i)
    debug ("heap[%d] = %d", i, heap[i]);
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

/* Max Heap */
void heapify(int* heap, int curr, int size) {
  int largest = curr;
  int l = 2*curr+1;	//left child
  int r = 2*curr+2;	//right child

  if(l<size && heap[l] > heap[largest])
    largest = l;
  if(r<size && heap[r] > heap[largest])
    largest = r;

  if(largest != curr) {
    swap(&heap[curr], &heap[largest]);

    heapify(heap, largest, size);
  }
}

/**
 * 0  1  2  3      4  5  6  7
 * [3][6][5][0]    [8][2][1][9]
 * |Internal Notes||  Leaves  |
 *
 * 		3
 * 	 /	       \
 * 	6		5
 *   /      \        /       \
 * 0 {A-}    8     2	      1
 * |
 * 9
 * Start Heapify 0th Node {A-} first a & then Bottom Up
 * Right to Left 0[idx-3] to 3[idx-0]
 * */
void heapSort(int* heap, int sz) {
  /**
     Build heap (rearrange array, assume you got
     input as array, ignore this par if its already heap)
     Heapify the nodes near the leaves first
     because their left & right subtree will
     be following heap property & then hepify
     parent internal notes (Bottom-Up)
  */
  /* Extram Map + Heapify Internal Nodes First */
  for (int i = ((sz/2) - 1); i >= 0; i--) {
    heapify(heap, i, sz);
    display_this(heap, sz);
  }

  for(int i=sz-1; i>0 ;--i) {
    //Swap heap root with last element
    swap(&heap[0], &heap[i]);

    heapify(heap, 0, i);	//Heapify root with heapsize = i
  }
}


void test() {
  int ret = 0;
  int heap2[] = { 9, 6, 8, 2, 1, 4, 3};	//Max-Heap
  //int heap[]  = { 5, 8, 3, 9, 4, 1, 7};
  //  int heap[] = {54, 72, 45, 27, 36, 39, 99, 21, 63, 69};
  int heap[] = {10, 9, 12, 6, 4, 7, 19, 13, 21, 39};
  int sz = sizeof(heap)/sizeof(heap[0]);
  heapSort(heap, sz);

  debug("Heap in ASC is:\n");
  for(int i=0; i<sz; ++i)
    debug("[%d]--> [%d] \n",i, heap[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=74 :Heap in ASC is:

   [test] L=76 :[0]--> [1]

   [test] L=76 :[1]--> [2]

   [test] L=76 :[2]--> [3]

   [test] L=76 :[3]--> [4]

   [test] L=76 :[4]--> [6]

   [test] L=76 :[5]--> [8]

   [test] L=76 :[6]--> [9]
**/

/**
   Time Complexity = O(LogN)
   SpaceComplexity = O(LogN)
   Log N is Height of the tree
**/
