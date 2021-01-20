/***
    minheap Implementation using C.
    Date : 19 January 2021.
    San Diego, CA, 92126.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "minheap.h"

struct minheap* minheap_create(int max_sz) {
  struct minheap *h = (struct minheap*) malloc(sizeof(struct minheap));
  if (h == NULL) {
    fprintf(stderr, "Not enough memory!\n");
    abort();
  }
  h->max_size = max_sz;
  h->cur_size = 0;
  h->array = (int *) malloc(sizeof(int) * (h->max_size+1));
  if (h->array == NULL) {
    fprintf(stderr, "Not enough memory!\n");
    abort();
  }
  debug("End !");
  return h;
}

void minheap_destroy(struct  minheap *hp) {
  assert(hp);
  free(hp->array);
  free(hp);
}

static void minheap_double_capacity(struct minheap *hp) {
  // create double the array
  int new_max_size = 2 * hp->max_size;
  int* new_array = (int*) malloc(sizeof(int)*(new_max_size+1));

  if (new_array == NULL) {
    fprintf(stderr, "Not enough memory!\n");
    abort();
  }
  /* copy old elements to new array */
  for(int i = 1; i <= hp->cur_size; i++) {
    new_array[i] = hp->array[i];
  }
  /* free old array and place new in position */
  free(hp->array);
  hp->array = new_array;
  hp->max_size = new_max_size;
}


static
void minheap_swap(struct minheap *h, int i, int j) {
  assert (h && i >=1 && i <= h->cur_size &&
	  j >= 1 && j <= h->cur_size);
  int tmp = h->array[i];
  h->array[i] = h->array[j];
  h->array[j] = tmp;
}

static
void minheap_fixup(struct minheap *h, int k) {
assert(h && k >= 1 && k <= h->cur_size);

debug("<Inserting K = %d >", k);
while (k>1 && h->array[k] < h->array[k/2]) {
    debug("Inserting K = %d k/2 = %d ", k, k/2);
    minheap_swap(h, k/2, k);
    k /= 2;
    debug("Inserting K = %d", k);
  }
}


static
void minheap_fixdown(struct minheap *h, int k) {
  assert(h);
  while (2*k <= h->cur_size) {
    int j = 2*k;
    if (j < h->cur_size && h->array[j+1] < h->array[j])
      j++;
    if (h->array[k] <= h->array[j])
      break;
    minheap_swap(h, k, j);
    k = j;
  }
}

void minheap_insert(struct minheap *h, int key) {
  assert(h);

  debug("<Inserting K = %d >", key);
  // make sure there is space
  if (h->cur_size == h->max_size)
    minheap_double_capacity(h);

  // add at the bottom, as a leaf
  h->array[++h->cur_size] = key;

  // fix its position
  minheap_fixup(h, h->cur_size);
}

int minheap_findmin(struct minheap *h) {
  if (minheap_is_empty(h)) {
    fprintf(stderr, "Heap is empty!\n");
    abort();
  }
  // min is always in first position
  return h->array[1];
}


void minheap_deletemin(struct minheap *h) {
  if (minheap_is_empty(h)) {
    fprintf(stderr, "Heap is empty!\n");
    abort();
  }
  // swap first with last
  minheap_swap(h, 1, h->cur_size);
  // delete last
  h->cur_size--;
  // fixdown first
  minheap_fixdown(h, 1);
}

int minheap_size(struct minheap *h) {
  assert(h);
  return h->cur_size;
}
int minheap_is_empty(struct minheap *h) {
  assert(h);
  return h->cur_size <= 0;
}

void minheap_clear(struct minheap *h) {
  assert(h);
  h->cur_size = 0;
}

struct minheap* minheap_heapify(const int* array, int n) {
  assert(array && n > 0);
  struct minheap *h = (struct minheap*) malloc(sizeof(struct minheap));
  if (h == NULL) {
    fprintf(stderr, "Not enough memory!\n");
    abort();
  }
  h->max_size = n;
  h->cur_size = 0;
  h->array = (int*) malloc(sizeof(int)*(h->max_size+1));
  if (h->array == NULL) {
    fprintf(stderr, "Not enough memory!\n");
    abort();
  }
  h->cur_size = n;
  for(int k = 0; k < n; k++)
    h->array[k+1] = array[k];
  for(int k = (h->max_size+1)/2; k > 0; k--)
    minheap_fixdown(h, k);
  return h;
}

/***
    => ./heap_main
    [main] Inserting num = 34
    [main] Inserting num = 0
    [main] Inserting num = 96
    [main] Inserting num = 88
    [main] Inserting num = 38
    [main] Inserting num = 23
    [main] Inserting num = 5
    [main] Inserting num = 9
    [main] Inserting num = 5
    [main] Inserting num = 15
    [main] Heap Deleting::    0
    [main] Heap Deleting::    5
    [main] Heap Deleting::    5
    [main] Heap Deleting::    9
    [main] Heap Deleting::   15
    [main] Heap Deleting::   23
    [main] Heap Deleting::   34
    [main] Heap Deleting::   38
    [main] Heap Deleting::   88
    [main] Heap Deleting::   96

    => ./heap_main
    [main] Inserting num = 67
    [main] Inserting num = 89
    [main] Inserting num = 4
    [main] Inserting num = 0
    [main] Inserting num = 68
    [main] Inserting num = 73
    [main] Inserting num = 20
    [main] Inserting num = 0
    [main] Inserting num = 79
    [main] Inserting num = 5
    [main] Heap Deleting::    0
    [main] Heap Deleting::    0
    [main] Heap Deleting::    4
    [main] Heap Deleting::    5
    [main] Heap Deleting::   20
    [main] Heap Deleting::   67
    [main] Heap Deleting::   68
    [main] Heap Deleting::   73
    [main] Heap Deleting::   79
    [main] Heap Deleting::   89
*/
