/***
    Heap Template
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed 19 Mar 2025 07:15:10 AM PDT
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdarg.h> // va_arg
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

struct heap {
  int* buf;
  int hSize;    // Runtime
  int capacity; // Total heap capacity
};

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int parent(int i) {
  return (i - 1) / 2;
}

// return the index of the left child
int left_child(int i) {
  return 2*i + 1;
}

// return the index of the right child
int right_child(int i) {
  return 2*i + 2;
}

struct heap* heap_init(int capacity) {
  struct heap* heap_Obj = (struct heap*)malloc(sizeof (struct heap));
  if(NULL == heap_Obj)
    return NULL;
  heap_Obj->buf = (int *)malloc(sizeof(int) * capacity);
  if(NULL == heap_Obj->buf) {
    free(heap_Obj);
    return NULL;
  }
  heap_Obj->hSize = 0;
  heap_Obj->capacity = capacity;
  return heap_Obj;
}

//void max_heapify(struct heap* heapObj, int root_index, int n)
void maxHeapify(struct heap* heapObj, int root_idx) {

  int largest = root_idx;                         // find the largest among 3 nodes
  int left_child_index  = left_child(root_idx);   // find left child node
  int right_child_index = right_child(root_idx);  // find right child node

  // Finding the index of the largest value among:
  // arr[root_index], arr[left_child_index] and arr[right_child_index]
  // check if the left node is larger than the current node
  if (left_child_index < heapObj->hSize && heapObj->buf[left_child_index] > heapObj->buf[largest]) {
    largest = left_child_index;
  }

  // check if the right node is larger than the current node
  if (right_child_index < heapObj->hSize && heapObj->buf[right_child_index] > heapObj->buf[largest]) {
    largest = right_child_index;
  }

  // swap the largest node with the current node
  // and repeat this process until the current node is larger than
  // the right and the left node
  // The largest among the three considered values will now be the root of the Max-Heap
  // represented by arr[root_index ... n - 1].
  if (largest != root_idx) {

    swap(heapObj->buf+largest, heapObj->buf+root_idx);
    maxHeapify(heapObj, largest);
  }
}

void minHeapify(struct heap* heap_Obj, int root_idx) {
  int largest = root_idx;
  int l_child = 2 * root_idx + 1;
  int r_child = 2 * root_idx + 2;

  if (l_child < heap_Obj->hSize && heap_Obj->buf[l_child] < heap_Obj->buf[largest])
    largest = l_child;

  if (r_child < heap_Obj->hSize && heap_Obj->buf[r_child] < heap_Obj->buf[largest])
    largest = r_child;

  if (largest != root_idx) {
    swap(&heap_Obj->buf[largest], &heap_Obj->buf[root_idx]);
    minHeapify(heap_Obj, largest);
  }
}

// Max Heap
void push1(struct heap* heap_Obj, int val) {
  if(heap_Obj->hSize >=  heap_Obj->capacity) {
    debug("Overflow Returning!");
    return;
  }

  heap_Obj->buf[heap_Obj->hSize] = val;
  int curr = heap_Obj->hSize;
  while(curr>0 && heap_Obj->buf[(curr-1)/2] > heap_Obj->buf[curr]) {
    swap(heap_Obj->buf+(curr-1)/2, heap_Obj->buf+curr);
    curr = (curr-1)/2;
  }
  heap_Obj->hSize += 1;
}

int pop1(struct heap* heap_Obj) {

  if(heap_Obj->hSize <= 0) {
    debug("Underflow, Returning!");
    return -1;
  }
  int val = heap_Obj->buf[0];
  heap_Obj->buf[0] = heap_Obj->buf[heap_Obj->hSize-1];
  heap_Obj->hSize -=1;
  maxHeapify(heap_Obj, 0);
  return val;
}

void push(struct heap* heapObj, int data) {
  if (heapObj->hSize >= heapObj->capacity) {
    printf("%s\n", "The heap is full. Cannot insert");
    return;
  }
  // first insert the time at the last position of the array
  // and move it up
  heapObj->buf[heapObj->hSize] = data; // Step 1 - Storing element to last node - As it is Zero Index array
  heapObj->hSize++;
  //  *n = *n + 1;  // Increase Heap Size


  // move up until the heap property satisfies
  int i = heapObj->hSize - 1;
  // TechDose - Percolate (झिरपणे)
  while (i != 0 && heapObj->buf[parent(i)] < heapObj->buf[i]) {
    swap(&heapObj->buf[parent(i)], &heapObj->buf[i]);
    i = parent(i); // i=i/2 - Parent
  }
}
// heap_pop
int pop(struct heap* heapObj) {
  int root;
  debug ("sticksSize = %d", heapObj->hSize);
  root = heapObj->buf[0];
  heapObj->buf[0] = heapObj->buf[heapObj->hSize - 1]; // Copy Last Element to the Root & Heapify
  heapObj->hSize -= 1;
  maxHeapify(heapObj, 0);

  return root;
}

int top(struct heap* heap_Obj) {
  return heap_Obj->buf[0];
}

void deleteRoot(struct heap* heap_Obj, int num) {
  int i;
  for (i=0; i<heap_Obj->hSize; i++) {
    if (num == heap_Obj->buf[i])
      break;
  }

  swap(&heap_Obj->buf[i], &heap_Obj->buf[heap_Obj->hSize - 1]);
  heap_Obj->hSize -= 1;
  for (int i=heap_Obj->hSize/2-1; i >= 0; i--) {
    maxHeapify(heap_Obj, i);
  }
}

void show_heap(struct heap *heap_Obj) {
  for(int i=0; i<heap_Obj->hSize; ++i)
    debug("->[%d]", heap_Obj->buf[i]);
  printf("\n");
}

void heap_free(struct heap* heap_Obj) {
  if(heap_Obj) {
    free(heap_Obj->buf);
    free(heap_Obj);
  }
}

/***** Logic To Test Code *****/
void test() {
  int k = 2;
  int arr[] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};//{3, 2, 1, 5, 6, 4};
  int arr_sz = sizeof(arr)/sizeof(arr[0]);
  int capacity = arr_sz;

  struct heap* heap_Obj = heap_init(capacity);
  for (int i=0; i<arr_sz; ++i)
    push(heap_Obj, arr[i]);

  debug("heap_Obj->hSize=%d", heap_Obj->hSize);
  show_heap(heap_Obj);

  for (int i=0; i<arr_sz; ++i) {
    if (heap_Obj->hSize > k) {
      pop(heap_Obj);
    }
  }
  debug("heap_Obj->hSize = %d Output = %d", heap_Obj->hSize, top(heap_Obj));
  heap_free(heap_Obj);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[209][0_heap_template.c]->[test] :| heap_Obj->hSize=10
   L=[194][0_heap_template.c]->[show_heap] :| ->[16]
   L=[194][0_heap_template.c]->[show_heap] :| ->[14]
   L=[194][0_heap_template.c]->[show_heap] :| ->[10]
   L=[194][0_heap_template.c]->[show_heap] :| ->[8]
   L=[194][0_heap_template.c]->[show_heap] :| ->[7]
   L=[194][0_heap_template.c]->[show_heap] :| ->[9]
   L=[194][0_heap_template.c]->[show_heap] :| ->[3]
   L=[194][0_heap_template.c]->[show_heap] :| ->[2]
   L=[194][0_heap_template.c]->[show_heap] :| ->[4]
   L=[194][0_heap_template.c]->[show_heap] :| ->[1]

   L=[165][0_heap_template.c]->[pop] :| sticksSize = 10
   L=[165][0_heap_template.c]->[pop] :| sticksSize = 9
   L=[165][0_heap_template.c]->[pop] :| sticksSize = 8
   L=[165][0_heap_template.c]->[pop] :| sticksSize = 7
   L=[165][0_heap_template.c]->[pop] :| sticksSize = 6
   L=[165][0_heap_template.c]->[pop] :| sticksSize = 5
   L=[165][0_heap_template.c]->[pop] :| sticksSize = 4
   L=[165][0_heap_template.c]->[pop] :| sticksSize = 3
   L=[217][0_heap_template.c]->[test] :| heap_Obj->hSize = 2 Output = 2
**/
