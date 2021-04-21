/***
    Medium: 1209. Remove All Adjacent Duplicates in String II
    https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/

    You are given a string s and an integer k, a k duplicate removal
    consists of choosing k adjacent and equal letters from s and removing
    them, causing the left and the right side of the deleted substring to
    concatenate together.

    We repeatedly make k duplicate removals on s until we no longer can.

    Return the final string after all such duplicate removals have been
    made. It is guaranteed that the answer is unique.

    Input: s = "abcd", k = 2
    Output: "abcd"
    Explanation: There's nothing to delete.

    Input: s = "deeedbbcccbdaa", k = 3
    Output: "aa"
    Explanation:
    First delete "eee" and "ccc", get "ddbbbdaa"
    Then delete "bbb", get "dddaa"
    Finally delete "ddd", get "aa"

    Input: s = "pbbcggttciiippooaais", k = 2
    Output: "ps"

    Constraints:
    1 <= s.length <= 105
    2 <= k <= 104
    s only contains lower case English letters.
    Date: 04/18/2021 April.
    San Diego, CA	
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


struct stack {
  int *array;
  int top;
  int len;
};

int atclib_push(struct stack *root, int i) {
  if (root->top == root->len-1) {
    debug("Stack is Full!");
    return -1;
  }
  root->top++;
  root->array[root->top] = i;
  //  debug("data = %d top=%d", i, root->top);
}

int atclib_pop(struct stack *root, int i) {
  if (root->top < 0) {
    debug("Stack is Empty!");
    return -1;
  }
  int ret = root->array[root->top];
  root->top = root->top-1;
  //  debug("ret = %d top=%d arr=%d", ret, root->top, root->array[ret]);
  return ret;
}

int atclib_top(struct stack *root, int i) {
  if (root->top < 0) {
    debug("Stack is Empty!");
    return -1;
  }
  root->top;
  //return root->array[root->top];
}

/* Needs to Fixed */
char * removeDuplicates2(char* s, int k) {
  int j = 0, len;
  len = strlen(s);
  struct stack at_stack = {NULL, 0, len};

  /* Allocate the stack */
  at_stack.array = malloc(sizeof(int) * (len * 2));
  if (!at_stack.array)
    return 0;

  for (int i = 0; i < len; ++i, ++j) {
    s[j] = s[i];
    debug("i=%d j=%d s[%d]=%c s[%d-1]=%c", i, j, i, s[i], j, s[j-1]);
    if (j == 0 || s[j] != s[j - 1]) {
      if (i == len-2)
	debug("Hmm!");
      else
	atclib_push(&at_stack, s[i]);
    } else if (atclib_top(&at_stack, i) == k) {
      atclib_pop(&at_stack, s[i]);
      j -= k;
      //j -= at_stack.array->top - 1;
    }
  }
  //  char subbuff[j];
  // memcpy(subbuff, &s[0], j);
  //subbuff[4] = '\0';

  debug("Reached!");
  debug("Reached = %c", at_stack.array[1]);
  debug("Reached = %c", at_stack.array[2]);
  debug("Reached = %c", at_stack.array[3]);
  debug("Reached = %c", at_stack.array[4]);
  //debug("Output = %s", subbuff);
  //return s.substr(0, j);
}

char * removeDuplicates(char * s, int k){
  int idx, len;

  idx = 0;
  len = strlen(s);
  int cnt[len];
  memset(cnt, 0, sizeof(int) * len);

  for (int i = 0; s[i]; i++) {
    s[idx] = s[i];
    if (idx > 0 && s[idx - 1] == s[idx])
      cnt[idx] = cnt[idx - 1] + 1;
    else
      cnt[idx] = 1;

    if (cnt[idx] == k)
      idx -= k;
    idx++;
  }
  s[idx] = 0;
  return s;
}

int main() {
  char s1[] = "deeedbbcccbdaa";
  char s[] = "deebbckko";
  int k = 2;
  char* ret = removeDuplicates(s, k);

  //debug("ret = %s", ret);
  return 0;
}

/**

 **/
