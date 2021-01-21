/***
	Ref :
	https://www.codesdope.com/blog/article/priority-queue-using-heap/
	https://www.geeksforgeeks.org/priority-queue-using-linked-list/
	Code for Min-Priority Queue - C
*/

#include <stdio.h>
#include "../../../at_lib.h"

int tree_array_size = 20;
int heap_size = 0;
const int INF = 100000;

void swap( int *a, int *b ) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}

//function to get right child of a node of a tree
int get_right_child(int A[], int index) {
  if((((2*index)+1) < tree_array_size) && (index >= 1))
    return (2*index)+1;
  return -1;
}

//function to get left child of a node of a tree
int get_left_child(int A[], int index) {
    if(((2*index) < tree_array_size) && (index >= 1))
        return 2*index;
    return -1;
}

//function to get the parent of a node of a tree
int get_parent(int A[], int index) {
  if ((index > 1) && (index < tree_array_size)) {
    return index/2;
  }
  return -1;
}

void min_heapify(int A[], int index) {
  int left_child_index = get_left_child(A, index);
  int right_child_index = get_right_child(A, index);

  // finding smallest among index, left child and right child
  int smallest = index;

  if ((left_child_index <= heap_size) && (left_child_index>0)) {
    if (A[left_child_index] < A[smallest]) {
      smallest = left_child_index;
    }
  }

  if ((right_child_index <= heap_size && (right_child_index>0))) {
    if (A[right_child_index] < A[smallest]) {
      smallest = right_child_index;
    }
  }

  // smallest is not the node, node is not a heap
  if (smallest != index) {
    swap(&A[index], &A[smallest]);
    min_heapify(A, smallest);
  }
}

void build_min_heap(int A[]) {
  int i;
  for(i=heap_size/2; i>=1; i--) {
    min_heapify(A, i);
  }
}

int minimum(int A[]) {
  return A[1];
}

int extract_min(int A[]) {
  int minm = A[1];
  A[1] = A[heap_size];
  heap_size--;
  min_heapify(A, 1);
  return minm;
}

void decrease_key(int A[], int index, int key) {
  A[index] = key;
  while((index>1) && (A[get_parent(A, index)] > A[index])) {
    swap(&A[index], &A[get_parent(A, index)]);
    index = get_parent(A, index);
  }
}

void increase_key(int A[], int index, int key) {
  A[index] = key;
  min_heapify(A, index);
}

void insert(int A[], int key) {
  heap_size++;
  A[heap_size] = INF;
  decrease_key(A, heap_size, key);
}

void print_heap(int A[]) {
  int i;
  for(i=1; i<=heap_size; i++) {
    printf("%d\n",A[i]);
  }
  printf("\n");
}

int main() {
  int A[tree_array_size];
  insert(A, 20);
  insert(A, 15);
  insert(A, 8);
  insert(A, 10);
  insert(A, 5);
  insert(A, 7);
  insert(A, 6);
  insert(A, 2);
  insert(A, 9);
  insert(A, 1);

  print_heap(A);

  increase_key(A, 5, 22);
  print_heap(A);

  printf("%d\n\n", minimum(A));
  printf("%d\n\n", extract_min(A));

  print_heap(A);

  printf("%d\n", extract_min(A));
  printf("%d\n", extract_min(A));
  printf("%d\n", extract_min(A));
  printf("%d\n", extract_min(A));
  printf("%d\n", extract_min(A));
  printf("%d\n", extract_min(A));
  printf("%d\n", extract_min(A));
  printf("%d\n", extract_min(A));
  printf("%d\n", extract_min(A));
  return 0;
}
