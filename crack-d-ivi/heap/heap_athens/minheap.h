#ifndef _MINHEAP_H
#define _MINHEAP_H

#define debug(str,args...) printf("[%s] [%s()] L=%d :"str"\n",__FILE__, __func__, __LINE__, ##args)

#define HEAP_SIZE 64

/***
    1. array is the array for the keys
    2. max_size+1 is the array size
    3. cur_size is the position of the last array element which is used
*/
struct minheap {
  int* array;
  int max_size;
  int cur_size;
};

struct minheap* minheap_create(int max_size);
struct minheap* minheap_heapify(const int* array, int n);

void minheap_destroy(struct minheap *);

int minheap_findmin(struct minheap *);
void minheap_deletemin(struct minheap *);
void minheap_insert(struct minheap *, int);

int minheap_is_empty(struct minheap *);
int minheap_size(struct minheap *);
void minheap_clear(struct minheap *);

#endif
