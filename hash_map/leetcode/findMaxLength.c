/***
    https://leetcode.com/problems/contiguous-array/
    Contiguous Array

    Given a binary array nums, return the maximum length
    of a contiguous subarray with an equal number of 0 and 1.

    Input: nums = [0,1]
    Output: 2
    Explanation: [0, 1] is the longest contiguous subarray with
    an equal number of 0 and 1.

    Input: nums = [0,1,0]
    Output: 2
    Explanation: [0, 1] (or [1, 0]) is a longest contiguous
    subarray with equal number of 0 and 1.

    Constraints:
    1 <= nums.length <= 105
    nums[i] is either 0 or 1.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 3 Feb 2022
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

#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })

// Hash Map :
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
  for(i=0;i<size;i++)
    t->list[i] = NULL;
  return t;
}

int hashCode(struct table *t,int key){
  if(key<0)
    return -(key%t->size);
  return key%t->size;
}

void insert(struct table *t,int key,int val) {
  int pos = hashCode(t,key);
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
  while(temp){
    if(temp->key==key) {
      return temp->val;
    }
    temp = temp->next;
  }
  return -2;
}

int findMaxLength(int* nums, int numsSize) {
  struct table *t = createTable(1000);
  int sum=0,max=0,idx;
  insert(t,0,-1);
  for(int i=0;i<numsSize;i++) {
      sum += (nums[i] == 1) ? 1 : -1;
      if((idx=lookup(t,sum))!=-2)
	max=max>i-idx?max:i-idx;
      else
	insert(t,sum,i);

    }
  return max;
}

//  Brute Force:Time Limit Exceeded
int findMaxLength_(int* nums, int numsSize) {
  int maxlen = 0;
  //    int ret[numsSize] = {0};
  for (int start = 0; start < numsSize; start++) {
    int zeroes = 0, ones = 0;
    for (int end = start; end < numsSize; end++) {
      if (nums[end] == 0) {
	zeroes++;
      } else {
	ones++;
      }
      if (zeroes == ones) {
	maxlen = max(maxlen, end - start + 1);
      }
    }
  }
  return maxlen;
}

void test() {
  int ret = 0;
  int nums[] = {0,1,0};
  int numsSize = 3;

  ret = findMaxLength(nums,numsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=152 :Output = 2
**/
