/***
    https://leetcode.com/problems/remove-k-digits
    402. Remove K Digits
    Given string num representing a non-negative integer num,
    and an integer k, return the smallest possible integer
    after removing k digits from num.

    Input: num = "1432219", k = 3
    Output: "1219"
    Explanation: Remove the three digits 4, 3, and 2 to form
    the new number 1219 which is the smallest.

    Input: num = "10200", k = 1
    Output: "200"
    Explanation: Remove the leading 1 and the number is 200.
    Note that the output must not contain leading zeroes.

    Input: num = "10", k = 2
    Output: "0"
    Explanation: Remove all the digits from the number
    and it is left with nothing which is 0.

    Constraints:
    1 <= k <= num.length <= 105
    num consists of only digits.
    num does not have any leading zeros except for the zero itself.

    https://www.youtube.com/watch?v=3QJzHqNAEXs&t=385s
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 10 Jan 2022
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


struct Stack {
  char val;
  struct Stack *next;
};

struct Stack *Initialize() {
  struct Stack *S = (struct Stack*)malloc(sizeof(struct Stack));
  S->next = NULL;
  return S;
}

void Push(struct Stack *S, char x) {
  struct Stack *tmp = (struct Stack*)malloc(sizeof(struct Stack));
  tmp->val = x;
  tmp->next = S->next;
  S->next = tmp;
}

void Pop(struct Stack *S) {
  struct Stack *tmp = S->next;
  S->next = tmp->next;
  tmp->next = NULL;
  free(tmp);
}

char Top(struct Stack *S) {
  return S->next->val;
}

int IsEmpty(struct Stack *S) {
  return S->next == NULL;
}

char* removeKdigits(char* num, int k) {
  debug("Input = %s", num);
  struct Stack *S = Initialize();

  for(int i = 0; i < strlen(num); ++i) {
    if (IsEmpty(S) == 0)
      debug("i->[%d] S->val = %c", i, S->next->val);
    while(S->next != NULL && num[i] < S->next->val && k > 0) {
      Pop(S);
      k--;
    }
    if(num[i] != '0' || !IsEmpty(S)) {
      Push(S, num[i]);
    }
    debug("S->val = %c Addr = %pK", S->next->val, S->next);
  }

  while(!IsEmpty(S) && k > 0) {
    Pop(S);
    k--;
  }
  debug("----------------------------");
  struct Stack *pos = S->next;
  int len = 0;
  while(pos) {
    debug("pos->val = %c Addr = %pK", pos->val, pos);
    len++;
    pos = pos->next;
  }
  debug("Len = %d", len);
  if (len == 0) {
    char *res = (char*)malloc(sizeof(char) * (2));
    res[0] = '0';
    res[1] = '\0';
    return res;
  }
  char *result = (char*)malloc(sizeof(char)*(len+1));
  int i = len - 1;
  while(S->next) {
    result[i] = Top(S);
    Pop(S);
    i--;
  }
  result[len] = '\0';
  return result;
}

char* removeKdigits_(char* num, int k) {
  int n = strlen(num);
  char stack[100000];
  int top = -1;

  for (int i = 0; i < n; i++) {
    while (top != -1 && k && stack[top] > num[i]) {
      --top;
      --k;
    }
    if (top != -1 || num[i] != '0')
      stack[++top] = num[i];
  }

  while (k-- && top != -1)
    --top;
	
  if (top == -1)
    return "0";

  while (top != -1)
    num[--n] = stack[top--];

  return num + n;
}

void test() {
  char num[] = "1432219";
  int k = 3;

  char*ret = removeKdigits(num, k);
  debug("Output = %s", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [removeKdigits] L=96 :Input = 1432219
   [removeKdigits] L=109 :S->val = 1 Addr = 0x234f440K
   [removeKdigits] L=101 :i->[1] S->val = 1
   [removeKdigits] L=109 :S->val = 4 Addr = 0x234f460K
   [removeKdigits] L=101 :i->[2] S->val = 4
   [removeKdigits] L=109 :S->val = 3 Addr = 0x234f460K
   [removeKdigits] L=101 :i->[3] S->val = 3
   [removeKdigits] L=109 :S->val = 2 Addr = 0x234f460K
   [removeKdigits] L=101 :i->[4] S->val = 2
   [removeKdigits] L=109 :S->val = 2 Addr = 0x234f480K
   [removeKdigits] L=101 :i->[5] S->val = 2
   [removeKdigits] L=109 :S->val = 1 Addr = 0x234f480K
   [removeKdigits] L=101 :i->[6] S->val = 1
   [removeKdigits] L=109 :S->val = 9 Addr = 0x234f4a0K
   [removeKdigits] L=116 :----------------------------
   [removeKdigits] L=120 :pos->val = 9 Addr = 0x234f4a0K
   [removeKdigits] L=120 :pos->val = 1 Addr = 0x234f480K
   [removeKdigits] L=120 :pos->val = 2 Addr = 0x234f460K
   [removeKdigits] L=120 :pos->val = 1 Addr = 0x234f440K
   [removeKdigits] L=124 :Len = 4
   [test] L=173 :Output = 1219
*/
/**
   Complexity Analysis

   Time complexity : O(N). Although there are nested loops,
   the inner loop is bounded to be run at most kk times
   globally. Together with the outer loop, we have the
   exact (N + k)(N+k) number of operations. Since 0<k≤N,
   the time complexity of the main loop is bounded within 2N.
   For the logic outside the main loop, it is clear to see
   that their time complexity is O(N). As a result, the
   overall time complexity of the algorithm is O(N).
   Space complexity : O(N). We have a stack which would
   hold all the input digits in the worst case.
**/
