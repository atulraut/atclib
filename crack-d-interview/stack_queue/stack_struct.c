#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SZ 5
typedef struct _stack {  
  int top;
  int *buf;
} stack;

stack *m_init(void  *_ptr, int sz);
int push(void *_ptr, int val);
int pop (void *_ptr);
int topElement(void *_ptr);
int isEmpty(void *_ptr);

int main () {
  int a;
  stack *sptr = NULL;
  stack s;
  sptr = m_init(&s, STACK_SZ);
  push(sptr, 10);
  printf("\nValue inserted = 10");
  push(sptr, 20);
  printf("\nValue inserted = 20");
  push(sptr, 30);
  printf("\nValue inserted = 30");
  a = pop(sptr);
  printf("\nThe poped element is %d \n",a);
  isEmpty(sptr);
  a = pop(sptr);
  printf("\nThe poped element is %d \n",a);
  a = topElement(sptr);
  printf("\nTop element is %d \n",a);
  a = pop(sptr);
  printf("\nThe poped element is %d \n",a);
  isEmpty(sptr);
  a = pop(sptr);
  printf("\nThe poped element is %d \n",a);
}

stack *m_init(void  *_ptr, int sz) {
  stack *s = (stack *)_ptr;
  memset((void *)s, 0, sizeof(stack));
  s->top = -1;
  s->buf = (int *)malloc(sz * sizeof(int));
  if(NULL == s->buf)
    return;
  else
    return s;
}
int push(void *_ptr, int val) {
  stack *s = (stack *)_ptr;
  if (s->top == STACK_SZ-1)
    return -1;
  s->top++;
  s->buf[s->top] = val;
  printf ("\n[push] top=%d", s->top);
}

int pop (void *_ptr) {
  int val;
  stack *s = (stack *)_ptr;
  if (s->top < 0)
    return -1;
  val = s->buf[s->top];
  s->top = s->top-1;
  printf ("\n[pop] top=%d", s->top);
  return val;
}

int topElement(void *_ptr) {
  stack *s = (stack *)_ptr;
  if (s->top < 0)
    return -1;
  return s->buf[s->top];
}

int isEmpty(void *_ptr) {
  stack *s = (stack *)_ptr;
  if(s->top < 0)
    printf ("[isEmpty] Empty S - top=%d", s->top);
  else
    printf ("[isEmpty] Not - top=%d", s->top);  
}
