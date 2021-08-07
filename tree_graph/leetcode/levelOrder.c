/***
    Medium : N-ary Tree Level Order Traversal

    Given an n-ary tree, return the level order traversal of its nodes' values.

    Nary-Tree input serialization is represented in their level order traversal,
    each group of children is separated by the null value (See examples).

    Input: root = [1,null,3,2,4,null,5,6]
    Output: [[1],[3,2,4],[5,6]]

    https://leetcode.com/problems/n-ary-tree-level-order-traversal/

    Status : Incomplete
    Date: 6 August 2021
    Fair Oaks, CA.
*/

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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/**
 * Definition for a Node.
 */
struct Node {
  int val;
  int numChildren;
  struct Node** children;
};

#define MAX_QUEUE_SIZE 10000

typedef struct {
  struct Node * arr[MAX_QUEUE_SIZE];
  int level_arr[MAX_QUEUE_SIZE];
  int front;
  int rear;
} Queue;

int isQueueEmpty(Queue * tree_queue) {
  if(tree_queue->front == -1)
    return 1;
  else
    return 0;
}

int isQueueFull(Queue * tree_queue) {
  if(tree_queue->rear == MAX_QUEUE_SIZE - 1)
    return 1;
  else
    return 0;
}

void enqueue(Queue * tree_queue, struct Node * tree_node, int level) {
  if(isQueueFull(tree_queue))
    return;

  tree_queue->arr[++(tree_queue->rear)] = tree_node;
  tree_queue->level_arr[tree_queue->rear] = level;

  if(tree_queue->front == -1)
    tree_queue->front = 0;
}

struct Node * dequeue(Queue * tree_queue, int * level) {
  if(isQueueEmpty(tree_queue)) {
    *level = 0;
    return NULL;
  }

  struct Node * ret_node = tree_queue->arr[tree_queue->front];
  *level = tree_queue->level_arr[tree_queue->front];

  if(tree_queue->front == tree_queue->rear) {
    tree_queue->front = -1;
    tree_queue->rear = -1;
  } else {
    (tree_queue->front)++;
  }
  return ret_node;
}

int height(struct Node * root) {
  if(root == NULL)
    return 0;

  if(root->numChildren == 0)
    return 1;

  int i=0;
  int * child_ptr = (int *)malloc(sizeof(int) * root->numChildren);
  int child_ptr_index = 0;

  for(i=0; i<root->numChildren; i++) {
    child_ptr[child_ptr_index++] = height(root->children[i]);
  }

  int max = 0;
  for(i=0; i<child_ptr_index; i++) {
    if(child_ptr[i] >= max)
      max = child_ptr[i];
  }

  return max+1;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
  if(root == NULL) {
    *returnSize = 0;
    *returnColumnSizes = NULL;
    return root;
  }
  int no_of_levels = height(root);

  int ** ret_ptr = (int **)malloc(sizeof(int *) * no_of_levels);
  int ret_ptr_index = -1;

  *returnColumnSizes = ( int *)malloc(sizeof(int) * no_of_levels);

  int column_arr_index = 0;


  Queue tree_queue;
  memset(tree_queue.arr, NULL, sizeof(tree_queue.arr));
  memset(tree_queue.level_arr, 0, sizeof(tree_queue.level_arr));
  tree_queue.front = -1;
  tree_queue.rear = -1;

  struct Node * tmp_ptr = root;
  int previous_level = 0;
  int current_level = 1;

  int tmp_arr_index = 0;
  enqueue(&tree_queue, root, current_level);

  int * tmp_arr = NULL;
  int parent_no_of_child = -1;

  while(!isQueueEmpty(&tree_queue)) {
    tmp_ptr = dequeue(&tree_queue, &current_level);

    if(current_level != previous_level) {
      //Create a array
      if(parent_no_of_child == -1)  { //Root Node
	parent_no_of_child = 1;
	tmp_arr = (int *)malloc(sizeof(int) * parent_no_of_child);
	parent_no_of_child = tmp_ptr->numChildren;

	*(*returnColumnSizes + column_arr_index) = 1;
	column_arr_index++;

      } else {
	tmp_arr = (int *)malloc(sizeof(int) * parent_no_of_child);
	*(*returnColumnSizes + column_arr_index) = parent_no_of_child;
	column_arr_index++;
	parent_no_of_child = tmp_ptr->numChildren;
      }

      tmp_arr_index = 0;
      ret_ptr_index++;

      ret_ptr[ret_ptr_index] = tmp_arr;
      ret_ptr[ret_ptr_index][tmp_arr_index++] = tmp_ptr->val;

    } else if(current_level == previous_level) {
      ret_ptr[ret_ptr_index][tmp_arr_index++]= tmp_ptr->val;
      parent_no_of_child += tmp_ptr->numChildren;
    }

    previous_level = current_level;

    int i=0;
    for(i=0; i<tmp_ptr->numChildren; i++) {
      if(tmp_ptr->children[i] != NULL)
	enqueue(&tree_queue, tmp_ptr->children[i], current_level+1);
    }
  }

  *returnSize = (ret_ptr_index+1);

  return ret_ptr;
}

int main () {
  int ret = 0;

  struct Node root[6];
  int returnSize;
  int* returnColumnSizes;

  int**op = levelOrder(root, &returnSize, &ireturnColumnSizes);

  debug("Output = %d", ret);
  return 0;
}

/**
   [[1],[3,2,4],[5,6]]
 **/
