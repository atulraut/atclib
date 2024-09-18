/***
    https://leetcode.com/problems/generate-parentheses/
    22. Generate Parentheses -  Medium

    Given n pairs of parentheses, write a function to generate all
    combinations of well-formed parentheses.

    Input: n = 3
    Output: ["((()))","(()())","(())()","()(())","()()()"]

    Input: n = 1
    Output: ["()"]

    Constraints:
    1 <= n <= 8
    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Aug 12, 2024
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

/*
  Time - catalan numbers 6c3/3+1 = 5
  Space-
***/
#defin ST_MAX 16

struct stack {
  char buf[ST_MAX];
  int sz;
};

void stack_init(struct stack* st) {
  st->sz = 0;
}

int stack_top(struct stack* st) {
  if (!st->sz)
    return -1;

  return st->buf[st->sz-1];
}

int stack_push(struct stack* st, char data) {
  if (st->sz >= ST_MAX)
    return -1;

  st->buf[st->sz++] = data;
  return 1;
}

int stack_pop(struct stack* st) {
  if (!st->sz)
    return -1;

  st->sz--;
  return 1;
}

char* generate_str_from_arr(char* buf, int sz) {
  char* str = (char *)malloc(sizeof(char) * (sz+1));
  strncpy(str, buf, sz);
  str[sz] = '\0';
  debug("str = %s", str);
  return str;
}
/*             Sub Problem Defination               Partial Soln */
void backtrack(int openN, int closeN, int n, struct stack* st, char** res, int* returnSize) {
  // Base Case : leaf worker
  if (openN == closeN && openN == n) { // well formed parenthesis is d constrain-backtrackng
    (*returnSize)++;
    res[*returnSize-1] = generate_str_from_arr(st->buf, st->sz);
    return;
  }

  // Recursive Case :
  if (openN < n) {
    stack_push(st, '{');
    backtrack(openN+1, closeN, n, st, res, returnSize);
    stack_pop(st);
  }
  if(closeN < openN) {
    stack_push(st, '}');
    backtrack(openN, closeN+1, n, st, res, returnSize);
    stack_pop(st);
  }
}

char** generateParenthesis(int n, int* returnSize) {
  struct stack st;
  char** res;
  *returnSize = 0;

  stack_init(&st);
  res = (char **)malloc((1<<(n+3)) * sizeof(char)); // 64 bytes
  backtrack(0, 0, n, &st, res, returnSize);
  return res;
}

void test() {

  char** ret;
  int n = 3;
  int returnSize;

  ret = generateParenthesis(n, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("[%s]", (char *)ret[i]);

}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[57] [stack_push] :| data={
   L=[58] [stack_push] :| st->buf[1]=
   L=[57] [stack_push] :| data={
   L=[58] [stack_push] :| st->buf[2]=
   L=[57] [stack_push] :| data={
   L=[58] [stack_push] :| st->buf[3]=
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[4]=
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[5]=
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[6]=
   L=[74] [generate_str_from_arr] :| str = {{{}}}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[3]=}
   L=[57] [stack_push] :| data={
   L=[58] [stack_push] :| st->buf[4]=}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[5]=}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[6]=
   L=[74] [generate_str_from_arr] :| str = {{}{}}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[4]=}
   L=[57] [stack_push] :| data={
   L=[58] [stack_push] :| st->buf[5]=}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[6]=
   L=[74] [generate_str_from_arr] :| str = {{}}{}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[2]=}
   L=[57] [stack_push] :| data={
   L=[58] [stack_push] :| st->buf[3]=}
   L=[57] [stack_push] :| data={
   L=[58] [stack_push] :| st->buf[4]={
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[5]=}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[6]=
   L=[74] [generate_str_from_arr] :| str = {}{{}}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[4]=}
   L=[57] [stack_push] :| data={
   L=[58] [stack_push] :| st->buf[5]=}
   L=[57] [stack_push] :| data=}
   L=[58] [stack_push] :| st->buf[6]=
   L=[74] [generate_str_from_arr] :| str = {}{}{}
   L=[118] [test] :| [{{{}}}]
   L=[118] [test] :| [{{}{}}]
   L=[118] [test] :| [{{}}{}]
   L=[118] [test] :| [{}{{}}]
   L=[118] [test] :| [{}{}{}]
**/
