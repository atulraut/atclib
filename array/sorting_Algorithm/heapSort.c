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

void heapify(int* heap, int curr, int size) {
  int largest = curr;
  int l = 2*curr+1;	//left child
  int r = 2*curr+2;	//right child

  if(l<size && heap[l] > heap[largest])
    largest = l;
  if(r<size && heap[r] > heap[largest])
    largest = r;

  if(largest!=curr) {
    int temp      = heap[curr];
    heap[curr]    = heap[largest];
    heap[largest] = temp;

    heapify(heap, largest, size);
  }
}

void heapSort(int* heap, int sz) {
  // Build heap (rearrange array)
  for (int i = sz / 2 - 1; i >= 0; i--)
    heapify(heap, 0, i);

  for(int i=sz-1; i>0 ;--i) {
    int temp = heap[0];	//Swap heap root with last element
    heap[0] = heap[i];
    heap[i] = temp;

    heapify(heap, 0, i);	//Heapify root with heapsize = i
  }
}

void test() {
  int ret = 0;
  int heap[] = { 9, 6, 8, 2, 1, 4, 3};	//Max-Heap
  int sz = 7;
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
