/***
 * LeetCode
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
 Date: 06/19/2020 09:07PM - PDT
 Logic: https://www.youtube.com/watch?v=-1jxt_DPl48
 Heap Sort Explain : https://www.youtube.com/watch?v=yAlOKmgq8do
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct max_heap {
  int h_size;
  int h_cap;
  int *m_h;
} max_heap;

void swap(int *a, int *b) {
  int temp=*a;
  *a=*b;
  *b=temp;
}

int parent(int i) {
  return (i-1) / 2;
}

int is_empty(max_heap* h) {
  return h->h_size == 0 ;
}

void max_heapify(max_heap *h, int sz, int i) {
  int largest = i;
  int l = 2*i + 1;
  int r = 2*i + 2;

  printf ("[%s] l=%d r=%d largest=%d sz=%d L=%d \n", __func__, l, r, largest, sz, __LINE__);

  if (l < sz && h->m_h[l] > h->m_h[largest])
    largest = l;

  if (r < sz && h->m_h[r] > h->m_h[largest])
    largest = r;

  printf ("[%s] l=%d r=%d largest=%d i=%d sz=%d L=%d \n", __func__, l, r, largest, i, sz, __LINE__);
  if (largest != i) {
      swap(&(h->m_h[i]), &(h->m_h[largest]));
      for(int j=0; j<sz; j++)
          printf ("<--> [%s] h->m_h[%d]=%d L=%d \n", __func__, j, h->m_h[j], __LINE__);
      max_heapify(h, sz, largest);
  }

  //  for(int i=0; i<h->h_cap; i++)
  //    printf ("[%s] h->m_h[%d] = %d L=%d \n", __func__, i, h->m_h[i], __LINE__);
}

void insertKey(max_heap* h, int k) {
  (h->h_size)++;
  int i = (h->h_size) - 1;
  h->m_h[i] = k;


  while (i != 0 && h->m_h[parent(i)] < h->m_h[i]) {
      swap(&(h->m_h[i]), &(h->m_h[parent(i)]));
      i = parent(i);
  }
}

int extract_max(max_heap* h) {

  if (h->h_size == 1) {
      (h->h_size)--;
      return h->m_h[0];
  }

  int root = h->m_h[0];
  printf ("[%s] Root=%d Last=%d  sz=%d L=%d \n", __func__, h->m_h[0],   h->m_h[(h->h_size)-1], ((h->h_size)-1) , __LINE__);
  h->m_h[0] = h->m_h[(h->h_size)-1];
  (h->h_size)--;
  max_heapify(h, h->h_size, 0);
  return root;
}



max_heap* create_max_heap(int capacity){
  max_heap* h = (max_heap*)(calloc(sizeof(max_heap),1));
  h->h_size = 0;
  h->h_cap = capacity;
  h->m_h = (int*)(calloc(sizeof(int), h->h_cap));
  return h;
}

int lastStoneWeight(int* stones, int stonesSize) {
  int i=0;
  max_heap *h = create_max_heap(stonesSize);

  for(i=0; i<stonesSize; i++) {
    printf ("[%s] sz=%d L=%d \n", __func__, h->h_size, __LINE__);
    h->m_h[(h->h_size)++] = stones[i];
  }

  for(i = (stonesSize/2)-1; i >= 0; i--)
    max_heapify(h, stonesSize, i);

  for(i=0; i<h->h_cap; i++)
    printf ("[%s] Post-ax_heapify h->m_h[%d] = %d L=%d \n", __func__, i, h->m_h[i], __LINE__);

  while(h->h_size > 1) {
    int x=extract_max(h);
    int y=extract_max(h);

    if(x > y)
      insertKey(h, x-y);
  }

  return is_empty(h) ? 0 : h->m_h[0];
}

int main() {
  int stones[] = {3, 14, 9, 7};
  //int stones[] = {2,7,4,1,8,1};
  int stonesSize = sizeof(stones) / sizeof(stones[0]);

  int ret = lastStoneWeight(stones, stonesSize);
  printf ("ret--> %d \n", ret);
}
