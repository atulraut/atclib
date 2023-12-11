/*
  Largest Unique Number
  Given an array of integers A, return the largest integer that
  only occurs once.
  If no integer occurs once, return -1.

  Input: [5,7,3,9,4,9,8,3,1]
  Output: 8
  Explanation:
  The maximum integer in the array is 9 but it is repeated.
  The number 8 occurs only once, so it's the answer.

  Input: [9,9,8,8]
  Output: -1
  Explanation:
  There is no number that occurs only once.

  Note:
  1 <= A.length <= 2000
  0 <= A[i] <= 1000

  Date: 3/4/21, Sun Dec 10 10:25:20 PM PST 2023
  San Diego, Folsom, CA
  Author : Atul Raut
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

struct node {
  int val;
  int key;
  struct node *next;
};

struct hashTable {
  int sz;
  struct node **hashList;
};

struct hashTable* m_createHashTable(int size) {

  struct hashTable* hObj;

  if ((hObj = (struct hashTable *) malloc(sizeof(struct hashTable))) == NULL)
    return NULL;
  hObj->sz = size;
  hObj->hashList = (struct node**)malloc(size * sizeof(struct node*));
  for (int i=0; i<size; i++)
    hObj->hashList[i] = NULL;

  return hObj;
}

/**
   Try value % array size (desire) as Index to Look Up.
   May be Collision Happen, so use self referntial structure of NODE.
   Collision Means --> Two different values Mapping to Same Index & we
   want both them present in hashmap DS.
   2 Issues -
   1. Collision - Chaining - Start a Linked List from that cell.
   2. False +Ve (Present 1) - Write the value itself into cell (instead of '1')
 **/
int m_getHashCode(struct hashTable *hObj, int key) {
  if (key < 0)
    return -(key % hObj->sz);
  return (key % hObj->sz);
}

static void hashRelease(struct hashTable *hObj) {
  struct node *curr, *tmp;

  for (int i = 0; i<hObj->sz; i++) {
    curr = hObj->hashList[i];
    while (curr != NULL) {
      tmp = curr->next;
      free(curr);
      curr = tmp;
    }
  }
  free(hObj->hashList);
  free(hObj);
}

void m_hashInsert(struct hashTable *hObj, int key, int value)  { // KEY(array Element), VALUE(array Index)

  int pos = m_getHashCode (hObj, key);
  struct node *list = hObj->hashList[pos];

  struct node *nn = (struct node *)malloc(sizeof(struct node));
  struct node *curr = list;

  debug ("pos=[%d] key=%d value=%d curr=%pK",pos, key, value, curr);
  /* Collision Detection : Check if node with matching key is already present */
  while (curr) {
    if (curr->key == key) {
      curr->val++;//  = value; frequency of element more than 1
      debug ("key = %d val = %d \n", key, curr->val);
      return;
    }
    curr = curr->next;
  } // while ends

  nn->val = 1;// value; frequency of element here
  nn->key = key;
  nn->next = list;
  hObj->hashList[pos] = nn;
  debug("key = %d val = %d \n", key, nn->val);
}

/**
   bottom up approch
**/
int m_hashFind (struct hashTable *hObj, int key) { // KEY == (array Element)
  int pos = m_getHashCode(hObj, key);
  struct node *list = hObj->hashList[pos];
  struct node *temp = list;
  // printf ("pos=[%d] key=%d temp=%pK \t",pos, key, temp);
  while (temp) {
    if (temp->key == key) { // array element present/found in hashMap
      //return 1;
      //      printf ("[%s] temp->key=%d temp->val=%d \n", __func__, temp->key, temp->val);
      // return key;
      return temp->val; // its frequency of occurance of particular array element/number
    } // if ends
    temp = temp->next;
  }
  return 0; // array element NOT found
  printf ("\n");
  return -1;
}

int largestUniqueNumber(int* arr, int arrSize){
  int minLength = arrSize;
  int max  = -1;

  struct hashTable* hObj = m_createHashTable(minLength); // Create HashMap for Less Size Array

  for (int i=0; i<minLength; ++i)
    m_hashInsert(hObj, arr[i], i+1);

  for (int i=0; i<minLength; ++i) {
    if (m_hashFind(hObj, arr[i]) == 1) {
      if (arr[i] > max)
	max = arr[i];
    }
  }
  return max;
}

int main () {
  int arr[] = {5,7,3,9,4,9,8,3,1};
  // int arr[] = {9, 9, 8, 8};
  //int arr[] = {-3,0,1,-3,1,1,1,-3,10,0};
  //int arr[] = {2, 2, 3};
  int sz = (sizeof(arr))/(sizeof(arr[0]));
  printf ("sz = %d \n", sz);
  int ans = largestUniqueNumber(arr, sz);
  printf ("--> O/P = %d \n", ans);
}

/**
   >> ./a.out
   sz = 9
   [m_hashInsert] L=116 :pos=[5] key=5 value=1 curr=(nil)K
   [m_hashInsert] L=131 :key = 5 val = 1

   [m_hashInsert] L=116 :pos=[7] key=7 value=2 curr=(nil)K
   [m_hashInsert] L=131 :key = 7 val = 1

   [m_hashInsert] L=116 :pos=[3] key=3 value=3 curr=(nil)K
   [m_hashInsert] L=131 :key = 3 val = 1

   [m_hashInsert] L=116 :pos=[0] key=9 value=4 curr=(nil)K
   [m_hashInsert] L=131 :key = 9 val = 1

   [m_hashInsert] L=116 :pos=[4] key=4 value=5 curr=(nil)K
   [m_hashInsert] L=131 :key = 4 val = 1

   [m_hashInsert] L=116 :pos=[0] key=9 value=6 curr=0x5648a3808780K
   [m_hashInsert] L=121 :key = 9 val = 2

   [m_hashInsert] L=116 :pos=[8] key=8 value=7 curr=(nil)K
   [m_hashInsert] L=131 :key = 8 val = 1

   [m_hashInsert] L=116 :pos=[3] key=3 value=8 curr=0x5648a3808760K
   [m_hashInsert] L=121 :key = 3 val = 2

   [m_hashInsert] L=116 :pos=[1] key=1 value=9 curr=(nil)K
   [m_hashInsert] L=131 :key = 1 val = 1

   --> O/P = 8
 */
