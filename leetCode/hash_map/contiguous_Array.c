/***
 * LeetCode : Contiguous Array
 * Given a binary array, find the maximum length of a contiguous subarray
 * with equal number of 0 and 1.
 * Example 1:
 * Input: [0,1]
 * Output: 2
 * Explanation: [0, 1] is the longest contiguous subarray with equal
 * number of 0 and 1.
 * Example 2:
 * Input: [0,1,0]
 * Output: 2
 * Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with
 * equal number of 0 and 1.
 * Note: The length of the given binary array will not exceed 50,000.
 * Logic : https://www.youtube.com/watch?v=9ZyLjjk536U
 * Sum   == Key
 * Index == Value
 * 0 1 2 3 4 5   --> Index
 * [ 1 1 0 0 1 1]
 * Sum  Index
 * Key  Value
 * | 1| --> 0
 * | 2| --> 1
 * | 3| --> 8
 * | 4| --> 0
 * Lengh of Subarray = (Current_Index - Map_Index)
 * Time Complexity - O(N)
 * Space Complexity - O(N)
 * Date: 06/20/2020 07:12PM Saturday.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Approch 1: */
struct node {
  int key;
  int val;
  struct node *next;
};
struct table {
  int size;
  struct node **list;
};

struct table *createTable(int size) {
  struct table *t = (struct table*)malloc(sizeof(struct table));
  t->size = size;
  t->list = (struct node**)malloc(sizeof(struct node*)*size);
  int i;

  for(i=0; i<size; i++)
    t->list[i] = NULL;

  return t;
}

void freeTable (struct table *obj) {
  free(obj->list);
  obj->list = NULL;
  free(obj);
  obj = NULL;
}

int hashCode(struct table *t, int key) {
  if(key < 0)
    return -(key % t->size);
  return key % t->size;
}

void insert(struct table *t, int key, int val) {
  int pos = hashCode(t,key);
  printf ("[%s] key=%d val=%d L=%d \n", __func__, key, val,  __LINE__);
  struct node *list = t->list[pos];
  struct node *newNode = (struct node*)malloc(sizeof(struct node));

  newNode->key = key;
  newNode->val = val;
  newNode->next = list;
  t->list[pos] = newNode;
}

int lookup(struct table *t,int key) {
  int pos = hashCode(t,key);
  struct node *list = t->list[pos];
  struct node *temp = list;

  while(temp) {
    if(temp->key == key)
      return temp->val;
    temp = temp->next;
  }
  return -2;
}

int findMaxLength(int* nums, int numsSize){
  int i;

  struct table *t = createTable((numsSize+1));
  int sum=0, longest_sub_array=0, max_index;

  insert(t,0,-1);

  for(i=0; i<numsSize; i++) {
    sum += (nums[i] == 1) ? 1 : -1; /* Calculate Current Sum Value */
    printf ("[%s] sum=%d i=%d L=%d \n", __func__, sum, i,  __LINE__);
    if((max_index = lookup(t, sum)) != -2) {
      longest_sub_array = longest_sub_array > i-max_index ? longest_sub_array : i-max_index;
      printf ("[%s] longest_sub_array=%d sum=%d i=%d L=%d \n", __func__, longest_sub_array, sum, i,  __LINE__);
    } else {
      printf ("[%s] sum=%d i=%d L=%d \n", __func__, sum, i,  __LINE__);
      insert(t,sum,i); /* Sum occured at first time */
    }
  }
  freeTable(t);

  return longest_sub_array;
}

int main () {
  int arr[] = {0, 1, 1, 0, 1};
  int sz = sizeof(arr) / sizeof(arr[0]);

  int ret = findMaxLength(arr, sz);
  printf ("[%s] ret=%d L=%d \n", __func__, ret,  __LINE__);

  return 0;
}
