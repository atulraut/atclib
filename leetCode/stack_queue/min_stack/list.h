#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SZ 5
typedef struct _stack {
  int top;
  int min;
  int *stabuf;
  int *minbuf;
} stack;

stack *m_init(void  *_ptr, int sz);
int push(void *_ptr, int val);
int pop (void *_ptr);
int topElement(void *_ptr);
int isEmpty(void *_ptr);
int getMin(void *_ptr);
int m_Display(void *_ptr);
int quit(void *_ptr);
