/***
    Hard: K Empty Slots
    You have n bulbs in a row numbered from 1 to n.
    Initially, all the bulbs are turned off.
    We turn on exactly one bulb every day until all
    bulbs are on after n days.

    You are given an array bulbs of length n where
    bulbs[i] = x means that on the (i+1)th day,
    we will turn on the bulb at position x
    where i is 0-indexed and x is 1-indexed.

    Given an integer k, return the minimum day number
    such that there exists two turned on bulbs that
    have exactly k bulbs between them that are all
    turned off. If there isn't such day, return -1.

    Input: bulbs = [1,3,2], k = 1
    Output: 2
    Explanation:
    On the first day: bulbs[0] = 1, first bulb is turned on: [1,0,0]
    On the second day: bulbs[1] = 3, third bulb is turned on: [1,0,1]
    On the third day: bulbs[2] = 2, second bulb is turned on: [1,1,1]
    We return 2 because on the second day, there were
    two on bulbs with one off bulb between them.

    Input: bulbs = [1,2,3], k = 1
    Output: -1

    Constraints:

    n == bulbs.length
    1 <= n <= 2 * 104
    1 <= bulbs[i] <= n
    bulbs is a permutation of numbers from 1 to n.
    0 <= k <= 2 * 104

    https://leetcode.com/problems/k-empty-slots/
    Date: 26 Sept 2021
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


struct Node {
  int val;
  struct Node* next;
  struct Node* prev;
  struct Node* left;
  struct Node* right;
};

//create new linked list node
void* createNode(struct Node* p,struct Node* n,int val){
  struct Node* new_node=malloc(sizeof(struct Node));
  new_node->val=val;
  new_node->next=n;
  new_node->prev=p;
  new_node->left=NULL;
  new_node->right=NULL;
  return new_node;
}
//insert into tree
void* insert(struct Node* p,struct Node* n,struct Node* root, int val){
  if (val<root->val){
    if (root->left){
      return insert(root->prev,root,root->left,val);
    }else{
      root->left=createNode(root->prev,root,val);
      root->prev=root->left;
      return root->left;
    }
  }else{
    if (root->right){
      return insert(root,root->next,root->right,val);
    }else{
      root->right=createNode(root,root->next,val);
      root->next=root->right;
      return root->right;
    }
  }
}

void delete(struct Node* root){
  struct Node* temp=root;
  while (temp->left){
    temp=temp->left;
  }
  while(temp){
    //printf("%d->",temp->val);
    struct Node* hold=temp->next;
    free(temp);
    temp=hold;
  }
}

int kEmptySlots(int* bulbs, int bulbsSize, int K) {
  if (K>bulbsSize){
    return -1;
  }
  //create tree root
  struct Node* root=createNode(NULL,NULL,bulbs[0]);
  for (int i =1;i<bulbsSize;i++){
    //add value into linkedlist tree thing, and gef the node back
    struct Node* temp=insert(root->prev,root->next,root,bulbs[i]);
    int s1=-1;
    int s2=-1;
    //get left distance
    if (temp->prev)
      s1=temp->val-temp->prev->val-1;
    //get right distance
    if (temp->next)
      s2=temp->next->val-temp->val-1;
    //check for win
    if (s1==K || s2==K){
      delete(root);
      return i+1;
    }
  }
  delete(root);
  return -1;
}

int main (int argc, char **argv) {
  int ret = 0;
  int bulbs[] = {1,3,2};
  int k = 1;
  int bulbsSize = 3;

  ret = kEmptySlots(bulbs, bulbsSize, k);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=143 :Output = 2
**/
