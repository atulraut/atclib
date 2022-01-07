/***
    https://leetcode.com/problems/linked-list-random-node/
    382. Linked List Random Node

    Given a singly linked list, return a random node's value
    from the linked list. Each node must have the same
    probability of being chosen.

    Implement the Solution class:
    Solution(ListNode head) Initializes the object with the integer array nums.
    int getRandom() Chooses a node randomly from the list and r
    eturns its value. All the nodes of the list should be equally
    likely to be choosen.

    Input
    ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
    [[[1, 2, 3]], [], [], [], [], []]
    Output
    [null, 1, 3, 2, 2, 3]

    Explanation
    Solution solution = new Solution([1, 2, 3]);
    solution.getRandom(); // return 1
    solution.getRandom(); // return 3
    solution.getRandom(); // return 2
    solution.getRandom(); // return 2
    solution.getRandom(); // return 3
    // getRandom() should return either 1, 2, or 3 randomly.
    Each element should have equal probability of returning.

    Constraints:
    The number of nodes in the linked list will be in the range [1, 104].
    -104 <= Node.val <= 104
    At most 104 calls will be made to getRandom.

    Follow up:
    What if the linked list is extremely large and its length is unknown to you?
    Could you solve this efficiently without using extra space?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 1/6/2022
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

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  struct ListNode *next;
};

typedef struct {
  struct ListNode **list;
  int nodeCount;
} Solution;

Solution* solutionCreate(struct ListNode* head) {
  Solution *sol = (Solution *)malloc(sizeof(Solution));
  sol->nodeCount = 0;
  struct ListNode *iter = head;
  while(iter){
    sol->nodeCount++;
    iter = iter->next;
  }
  sol->list = (struct ListNode **)calloc(sizeof(struct ListNode *), sol->nodeCount);
  iter = head;
  for(int i=0; i<sol->nodeCount; i++){
    sol->list[i] = iter;
    iter=iter->next;
  }
  return sol;
}

int solutionGetRandom(Solution* obj) {
  int rand_idx = rand() % obj->nodeCount;
  struct ListNode *tmp = obj->list[rand_idx];
  return tmp->val;
}

void solutionFree(Solution* obj) {
  free(obj->list);
  free(obj);
}

void push(struct ListNode** head_ref, int val) {
  struct ListNode* nn = (struct ListNode*)malloc(sizeof(struct ListNode));
  nn->val = val;
  nn->next = (*head_ref);
  (*head_ref) = nn;
}

void printList(struct ListNode* head) {
  struct ListNode* trav = head;
  while (trav != NULL) {
    debug("%d  ", trav->val);
    trav = trav->next;
  }
}

void test_solutionGetRandom() {
  int ret = 0;
  struct ListNode* head = NULL;

  push(&head, 1);
  push(&head, 2);
  push(&head, 3);
  debug("Given linked list\n");
  printList(head);

  Solution* obj = solutionCreate(head);
  ret = solutionGetRandom(obj);
  debug("Output = %d", ret);
  ret = solutionGetRandom(obj);
  debug("Output = %d", ret);
  ret = solutionGetRandom(obj);
  debug("Output = %d", ret);
  ret = solutionGetRandom(obj);
  debug("Output = %d", ret);
  ret = solutionGetRandom(obj);
  debug("Output = %d", ret);
  ret = solutionGetRandom(obj);
  debug("Output = %d", ret);
  ret = solutionGetRandom(obj);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test_solutionGetRandom();
  return 0;
}
`
/**
   => ./a.out
   [test_solutionGetRandom] L=135 :Given linked list

   [printList] L=123 :3
   [printList] L=123 :2
   [printList] L=123 :1
   [test_solutionGetRandom] L=140 :Output = 2
   [test_solutionGetRandom] L=142 :Output = 2
   [test_solutionGetRandom] L=144 :Output = 3
   [test_solutionGetRandom] L=146 :Output = 2
   [test_solutionGetRandom] L=148 :Output = 1
   [test_solutionGetRandom] L=150 :Output = 2
   [test_solutionGetRandom] L=152 :Output = 2
**/
