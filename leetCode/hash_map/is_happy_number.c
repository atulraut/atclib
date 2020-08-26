/*
  Ref: https://leetcode.com/problems/happy-number/
  Write an algorithm to determine if a number n is "happy".

  A happy number is a number defined by the following process:
  Starting with any positive integer, replace the number by the
  sum of the squares of its digits, and repeat the process until
  the number equals 1 (where it will stay), or it loops endlessly
  in a cycle which does not include 1. Those numbers for which
  this process ends in 1 are happy numbers.
  Return True if n is a happy number, and False if not.
  Example:
  Input: 19
  Output: true
  Explanation: xy = x^2 + y^2 = ?
    1^2 + 9^2 = 1 + 81  = 82
    8^2 + 2^2 = 64 + 4  = 68
    6^2 + 8^2 = 36 + 64 = 100
    1^2 + 0^2 + 1 + 0   = 1

  Take a note of endless loop: e.g.29 - @A=29 - B - C - D - @A=29 or @C=29 Again Found means Endless Loop.
  (4)  A (1)
B            C
  (3)  D (2)
    https://www.youtube.com/watch?v=Egw03gI-Tf0
*/

#include <stdio.h>
#include <stdlib.h>

#define sz 1024

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

int hashCode(struct table *t,int key) {
    if(key<0)
        return -(key%t->size);
    return key%t->size;
}

void insert(struct table *t,int key) {
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];

    printf ("[%s] 1] pos=%d key=%d list = %p L=%d\n",__func__, pos, key, list, __LINE__);

    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    struct node *temp = list;

    while(temp) {
        if(temp->key==key) {
            temp->val++;
            printf ("[%s] temp = %p key=%d val=%d L=%d\n",__func__, temp, temp->key, temp->val, __LINE__);
            return;
        }
        temp = temp->next;
    }

    newNode->key = key;
    newNode->val = 1;
    newNode->next = list;
    t->list[pos] = newNode;

    printf ("[%s] newNode = %p key=%d val=%d L=%d\n",__func__, newNode, newNode->key, newNode->val, __LINE__);
}

int lookup(struct table *t, int key) {
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    printf ("[%s] 1] pos=%d key=%d list = %p L=%d\n",__func__, pos, key, list, __LINE__);
    struct node *temp = list;
    while(temp) {
        printf ("[%s] 2] temp->key = %d L=%d ",__func__, temp->key, __LINE__);
        if(temp->key==key){
           return temp->val++;;
        }
        temp = temp->next;
    }
    printf ("[%s] 3] key = %d L=%d\n",__func__, key, __LINE__);
    return -1;
}

int isHappy(int n) {
  int v, val;x
  int index;

  struct table *t = createTable(sz);
  //  insert(t,0);

  while(1) {
    val = 0;

    while (n) {
      index = n % 10;
      val += index * index;
      n /= 10;
      printf ("[%s] index=%d val=%d n=%d \n", __func__, index, val, n);
    } // ends

    if(1 == val)
      return 1;
    else if ( (v=lookup(t, val)) != -1 || (v=lookup(t, val)) == val) {
      printf ("[%s] --> Detected Loop, Returning v=%d val=%d \n", __func__, v, val);
      return -1;
    }
    /* Push Element into HashMap, but we make sure before pushing any number
     * we check if number already present in HashMpay using lookup, then
     * we bail out as we found there is endless loop.
    */
    insert(t, val);
    /* Update n to new reduced value val & continue search/lookup */
    n = val;
  }
  return -1;
}

int main () {
  int num = 19;
  //int num = 2;

  if(isHappy(num) > 0)
    printf ("[%s] Is Happye Number --> %d \n", __func__, num);
  else
    printf ("[%s] Is NOT Happye Number --> %d \n", __func__, num);
  return 0;
}

/*
=> ./a.out
[isHappy] index=9 val=81 n=1
[isHappy] index=1 val=82 n=0
[lookup] 1] pos=82 key=82 list = (nil) L=88
[lookup] 3] key = 82 L=97
[lookup] 1] pos=82 key=82 list = (nil) L=88
[lookup] 3] key = 82 L=97
[insert] 1] pos=82 key=82 list = (nil) L=63
[insert] newNode = 0x21de450 key=82 val=1 L=82
[isHappy] index=2 val=4 n=8
[isHappy] index=8 val=68 n=0
[lookup] 1] pos=68 key=68 list = (nil) L=88
[lookup] 3] key = 68 L=97
[lookup] 1] pos=68 key=68 list = (nil) L=88
[lookup] 3] key = 68 L=97
[insert] 1] pos=68 key=68 list = (nil) L=63
[insert] newNode = 0x21de470 key=68 val=1 L=82
[isHappy] index=8 val=64 n=6
[isHappy] index=6 val=100 n=0
[lookup] 1] pos=100 key=100 list = (nil) L=88
[lookup] 3] key = 100 L=97
[lookup] 1] pos=100 key=100 list = (nil) L=88
[lookup] 3] key = 100 L=97
[insert] 1] pos=100 key=100 list = (nil) L=63
[insert] newNode = 0x21de490 key=100 val=1 L=82
[isHappy] index=0 val=0 n=10
[isHappy] index=0 val=0 n=1
[isHappy] index=1 val=1 n=0
[main] Is Happye Number --> 19
*/
