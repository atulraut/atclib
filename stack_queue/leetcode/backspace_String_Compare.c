/*
  LeetCode: Backspace String Compare
  Given two strings S and T, return if they are equal when both are
  typed into empty text editors. # means a backspace character(DEL Char).
  Note that after backspacing an empty text, the text will continue empty.
  Example 1:
  Input: S = "ab#c", T = "ad#c"
  Output: true
  Explanation: Both S and T become "ac".
  Example 2:
  Input: S = "ab##", T = "c#d#"
  Output: true
  Explanation: Both S and T become "".
  Example 3:
  Input: S = "a##c", T = "#a#c"
  Output: true
  Explanation: Both S and T become "c".
  Example 4:
  Input: S = "a#c", T = "b"
  Output: false
  Explanation: S becomes "c" while T becomes "b".
  Note:
    1 <= S.length <= 200
    1 <= T.length <= 200
    S and T only contain lowercase letters and '#' characters.
    Follow up:
    Can you solve it in O(N) time and O(1) space?
    Ref:
    https://www.youtube.com/watch?v=96-d8ZPjHeE - Approch 1
    https://www.youtube.com/watch?v=nxo_4FzXLxU&list=PLEJXowNB4kPwCPVjDv6KsAsThtDOCQUok&index=9 - Approch 2 - Explain well!
    https://www.youtube.com/watch?v=vgog1EuEJYQ - Approch 3
    Date: 05/26/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
  int top;
  int size;
  int *buf;
};

struct stack *m_init(void  *_ptr, int sz) {
  struct stack *s = (struct stack *)_ptr;
  if(NULL == s) {
	printf ("memset needs valid pointer \n");
	exit(1);
  }
  memset((void *)s, 0, sizeof(struct stack));
  s->top = 0;
  s->size = sz;
  s->buf = (int *)malloc(sz * sizeof(int));
  if(NULL == s->buf)
    return NULL;
  else {
    memset((void *)s->buf, 0, sizeof(int));
    return s;
  }
}
int push(void *_ptr, int val) {
  struct stack *s = (struct stack *)_ptr;
  if (s->top == s->size)
    return -1;
  s->top++;
  s->buf[s->top] = val;
  printf ("\n[push] top=%d val=%d \n", s->top, val);
  return 0;
}

int pop (void *_ptr) {
  int val;
  struct stack *s = (struct stack *)_ptr;
  if (s->top < 0)
    return -1;
  val = s->buf[s->top];
  s->top = s->top-1;
  printf ("\n[pop] top=%d val=%d \n", s->top, val);
  return val;
}

int topElement(void *_ptr) {
  struct stack *s = (struct stack *)_ptr;
  if (s->top < 0)
    return -1;
  return s->buf[s->top];
}

int isEmpty(void *_ptr) {
  struct stack *s = (struct stack *)_ptr;
  if(s->top < 0) {
    printf ("[isEmpty] Empty S - top=%d \n", s->top);
    return -1;
  } else {
    printf ("[isEmpty] Not - top=%d \n", s->top);
    return s->top;
  }
}

/* Approch #1 */
int backspaceCompare(char *s, char *t){
  int i;
  int lens = strlen(s);
  int lent = strlen(t);
  struct stack *sptr = NULL;
  struct stack *tptr = NULL;
  struct stack ss, st;

  sptr = m_init(&ss, lens);
  tptr = m_init(&st, lent);

  /* source string */
  for (i=0; i<lens; i++) {
    printf ("[%s] char=%c L=%d\n", __func__, s[i], __LINE__);
    if(s[i] != '#') {
      push(sptr, s[i]);
    } else if (isEmpty(sptr) > 0) {
      pop(sptr);
    }
  }

  /* target string */
  for (i=0; i<lent; i++) {
    printf ("[%s] char=%c L=%d\n", __func__, t[i], __LINE__);
    if(t[i] != '#') {
      push(tptr, t[i]);
    } else if (isEmpty(tptr) > 0) {
      pop(tptr);
    }
  }

  printf ("[%s] -> STOP = %d L=%d\n",__func__,  sptr->top, __LINE__ );
  printf ("[%s] -> TTOP = %d L=%d\n",__func__,  tptr->top, __LINE__ );

  while (isEmpty(sptr)) {
    char current = pop(sptr);
    if ( isEmpty(tptr) < 0 || pop(tptr) != current) {
	return -1; /* flase */
    }
  }

  /* Free Allocations */
  if (sptr->buf) {
    free(sptr->buf);
  }
  if (tptr->buf) {
    free(tptr->buf);
  }

  printf ("[%s] -> sptr = %d tptr = %d L=%d\n",__func__,  isEmpty(sptr), isEmpty(tptr), __LINE__ );
  if ((isEmpty(sptr) == isEmpty(tptr)))
    return 1;
  else
    return -1;

}

int main () {
  //char *src = "aaa###a";
  //char *tar = "aaaa###a";
  //char *src = "ab#c";
  //char *tar = "ad#c";
  //char *src = "ab##";
  //char *tar = "c#d#";
  //char *src = "a##c";
  //char *tar = "#a#c";
  char *src = "a#c";
  char *tar = "b";

  if (backspaceCompare(src, tar) > 0)
    printf ("[%s] -> SUCCESS! \n",__func__);
  else
    printf ("[%s] -> FAILED!! \n",__func__);
  return 0;
}
