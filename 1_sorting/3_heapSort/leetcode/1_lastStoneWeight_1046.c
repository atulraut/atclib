/***
    https://leetcode.com/problems/last-stone-weight/

    1046. Last Stone Weight

    We have a collection of stones, each stone has a positive integer weight.
    Each turn, we choose the two heaviest stones and smash them together.
    Suppose the stones have weights x and y with x <= y.  The result of this smash is:
    If x == y, both stones are totally destroyed;
    If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
    At the end, there is at most 1 stone left.  Return the weight of this stone (or 0 if there are no stones left.)
    Example 1:
    Input: [2,7,4,1,8,1]
    Output: 1
    Explanation:
    We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
    we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
    we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
    we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of last stone.

    Note:
    1 <= stones.length <= 30
    1 <= stones[i] <= 1000

    Date:
    06/19/2020 09:07PM - PDT
    Sat Dec 31 22:15:58 PST 2022

    Logic: https://www.youtube.com/watch?v=-1jxt_DPl48
    Heap Sort Explain : https://www.youtube.com/watch?v=yAlOKmgq8do

    #Amazon
*/
/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------- Micro --------------------------------------*/

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

typedef struct max_heap {
  int h_size; // Current Heap Size (Runtime)
  int h_cap; // Heap Capacity init time
  int *buf;  // Heap Holder Buffer
} max_heap;

void swap(int *a, int *b) {
  int temp=*a;
  *a=*b;
  *b=temp;
}

int parent(int i) {
  return (i-1) / 2;
}

int is_empty(max_heap* thisHeap) {
  return thisHeap->h_size == 0 ;
}

// Top-To-Down & Left-To-Right we talk this Binary Tree
void max_heapify(max_heap* thisHeap, int root_index, int sz) {

  int largest = root_index;
  int left_child_index = 2*root_index + 1;
  int right_child_index = 2*root_index + 2;

  // check if the left node is larger than the current node
  if (left_child_index < sz && thisHeap->buf[left_child_index] > thisHeap->buf[largest])
    largest = left_child_index;

  // check if the right node is larger than the current node
  if (right_child_index < sz && thisHeap->buf[right_child_index] > thisHeap->buf[largest])
    largest = right_child_index;

  debug ("larget=%d root_idx=%d left=%d right=%d", largest, root_index, left_child_index, right_child_index);
  if (largest != root_index) {

      swap(&(thisHeap->buf[root_index]), &(thisHeap->buf[largest]));
      debug("[%d][%d][%d][%d]", thisHeap->buf[0], thisHeap->buf[1], thisHeap->buf[2], thisHeap->buf[3]);
      max_heapify(thisHeap, largest, sz);
  }
}

/***
    Insert Element: In a complete binary tree insert Elements
    at last level from left to right.
    Algo:
    1] Insert Node at end of heap (Left to Right), increase heap Size.
    2] Percolate up till -
    a] Parent > Current Node             - Other cond in while loop
    b] Current Node is root of the tree. - i != 0 (condtion)
    Time - O(logN)
**/
void insertKey(max_heap* thisHeap, int k) {

  (thisHeap->h_size)++;
  int i = (thisHeap->h_size) - 1;
  thisHeap->buf[i] = k;

  while (i != 0 && thisHeap->buf[parent(i)] < thisHeap->buf[i]) {
      swap(&(thisHeap->buf[i]), &(thisHeap->buf[parent(i)]));
      i = parent(i);
  }
}

/*
  1] Save the Max Value
  2] Copy Last to Root
  3] Remove Last : Decrease HeapSize
  4] Heapify Root
*/
int extract_max(max_heap* thisHeap) {

  if (thisHeap->h_size == 1) {
      (thisHeap->h_size)--;
      return thisHeap->buf[0];
  }

  int root = thisHeap->buf[0];

  thisHeap->buf[0] = thisHeap->buf[(thisHeap->h_size)-1];
  (thisHeap->h_size)--;
  max_heapify(thisHeap, 0, thisHeap->h_size);

  return root;
}

max_heap* create_max_heap(int capacity) {
  max_heap* h = (max_heap*)(calloc(sizeof(max_heap),1));
  h->h_size = 0;
  h->h_cap = capacity;
  h->buf = (int*)(calloc(sizeof(int), h->h_cap));
  return h;
}

int lastStoneWeight(int* stones, int stonesSize) {

  max_heap *thisHeap = create_max_heap(stonesSize);

  for(int i=0; i<stonesSize; i++)
    thisHeap->buf[(thisHeap->h_size)++] = stones[i];

  // Logic To Build Max Heap - Start from Inner-Node
  for(int i = (stonesSize/2)-1; i >= 0; i--) {
    debug("max_heapify = %d", i);
    max_heapify(thisHeap, i, stonesSize);
  }

  for(int i=0; i<thisHeap->h_cap; i++)
    debug("Post-max_heapify thisHeap->buf[%d] = %d", i, thisHeap->buf[i]);

  // [Extract Max Logic]
  while(thisHeap->h_size > 1) {
    int x = extract_max(thisHeap);
    int y = extract_max(thisHeap);

    // Insert New Item to Heap & Heapify
    if(x > y)
      insertKey(thisHeap, x-y);
  }

  // This is Max-Heap Hence return the Root
  return is_empty(thisHeap) ? 0 : thisHeap->buf[0];
}

void test() {
  int stones[] = {3, 14, 9, 7};
  //int stones[] = {2,7,4,1,8,1};
  int stonesSize = sizeof(stones) / sizeof(stones[0]);

  int ret = lastStoneWeight(stones, stonesSize);
  printf ("ret--> %d \n", ret);
}

int main() {
  test();
}

/***
    => ./a.out
    [lastStoneWeight] L=144 :Post-max_heapify thisHeap->buf[0] = 14
    [lastStoneWeight] L=144 :Post-max_heapify thisHeap->buf[1] = 7
    [lastStoneWeight] L=144 :Post-max_heapify thisHeap->buf[2] = 9
    [lastStoneWeight] L=144 :Post-max_heapify thisHeap->buf[3] = 3
    ret--> 1
*/

/***
 // Debug Version
 => ./a.out
 [lastStoneWeight] L=148 :max_heapify = 1
 [max_heapify] L=78 :larget=1 root_idx=1 left=3 right=4
 [lastStoneWeight] L=148 :max_heapify = 0
 [max_heapify] L=78 :larget=1 root_idx=0 left=1 right=2
 [max_heapify] L=82 :[14][3][9][7]
 [max_heapify] L=78 :larget=3 root_idx=1 left=3 right=4
 [max_heapify] L=82 :[14][7][9][3]
 [max_heapify] L=78 :larget=3 root_idx=3 left=7 right=8
 [lastStoneWeight] L=153 :Post-max_heapify thisHeap->buf[0] = 14
 [lastStoneWeight] L=153 :Post-max_heapify thisHeap->buf[1] = 7
 [lastStoneWeight] L=153 :Post-max_heapify thisHeap->buf[2] = 9
 [lastStoneWeight] L=153 :Post-max_heapify thisHeap->buf[3] = 3
 [max_heapify] L=78 :larget=2 root_idx=0 left=1 right=2
 [max_heapify] L=82 :[9][7][3][3]
 [max_heapify] L=78 :larget=2 root_idx=2 left=5 right=6
 [max_heapify] L=78 :larget=1 root_idx=0 left=1 right=2
 [max_heapify] L=82 :[7][3][3][3]
 [max_heapify] L=78 :larget=1 root_idx=1 left=3 right=4
 [max_heapify] L=78 :larget=0 root_idx=0 left=1 right=2
 [max_heapify] L=78 :larget=0 root_idx=0 left=1 right=2
 [max_heapify] L=78 :larget=0 root_idx=0 left=1 right=2
 ret--> 1
 *
