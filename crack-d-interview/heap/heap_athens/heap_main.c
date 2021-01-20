#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minheap.h"

int main() {
  int i, num;
  srand(time(NULL));

  debug("atclib: Create MiniHeap!");
  struct minheap *hp = minheap_create(HEAP_SIZE);

  /*
  for(i = 0; i < 10; i++) {
    num = rand() % 100;
    printf ("[%s] Inserting num = %d \n", __func__, num);
    minheap_insert(hp, num);
  }
  */

  debug ("Start Inserting Elements!");
  minheap_insert(hp, 2);
  minheap_insert(hp, 1);
  minheap_insert(hp, 3);
  minheap_insert(hp, 4);
  minheap_insert(hp, 9);
  minheap_insert(hp, 0);
  minheap_insert(hp, 7);

  while(!minheap_is_empty(hp)) {
    printf("[%s] Heap Deleting:: %4d \n",__func__, minheap_findmin(hp));
    minheap_deletemin(hp);
  }

  minheap_destroy(hp);

  return 0;
}
