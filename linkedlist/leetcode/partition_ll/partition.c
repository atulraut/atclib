/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* partition(struct ListNode* head, int x) {
  struct ListNode *before_x = (struct ListNode *) malloc (sizeof(struct ListNode));
  struct ListNode *after_x = (struct ListNode *) malloc (sizeof(struct ListNode));

  struct ListNode *dummy_after_x = (struct ListNode *) malloc (sizeof(struct ListNode));
  struct ListNode *dummy_before_x = (struct ListNode *) malloc (sizeof(struct ListNode));

  dummy_after_x = after_x;
  dummy_before_x = before_x;


  while(head != NULL) {
    if (head->val < x) {
      before_x->next = head;
      before_x = before_x->next;
    }
    else {
      after_x->next = head;
      after_x = after_x->next;
    }
    head = head->next;
  }

  after_x->next = NULL;
  before_x->next = dummy_after_x->next;
  return dummy_before_x->next;
}

/***
    Medium : 19. Remove Nth Node From End of List
    https://leetcode.com/problems/remove-nth-node-from-end-of-list/
    Given the head of a linked list, remove the nth node from the
    end of the list and return its head.

    Follow up: Could you do this in one pass?
    Input: head = [1,2,3,4,5], n = 2
    Output: [1,2,3,5]


    Input: head = [1], n = 1
    Output: []

    Input: head = [1,2], n = 1
    Output: [1]

    Constraints:
    The number of nodes in the list is sz.
    1 <= sz <= 30
    0 <= Node.val <= 100
    1 <= n <= sz
*/
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  struct ListNode *new_head = (struct ListNode*)malloc(sizeof(struct ListNode));
  new_head->next = head;
  int length = 0;
  struct ListNode *curr = head;

  while (curr != NULL) {
    length++;
    curr = curr->next;
  }

  length -= n;
  curr = new_head;

  while (length > 0) {
    length--;
    curr = curr->next;
  }

  curr->next = curr->next->next;
  return new_head->next;
}
