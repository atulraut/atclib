#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_node {
  int num;
  struct stack_node *next;
};

struct stack_type {
  struct stack_node *top;
};

struct stack_type* m_init_s(void *_ptr) {
  struct stack_type *st = (struct stack_type *)_ptr;
  st = (struct stack_type*)malloc(sizeof(struct stack_type));
  if(NULL == st)
    return (void *)NULL;
  st->top = NULL;
  return st;
}

int push(void *_ptr, int val) {
  struct stack_type *s = (struct stack_type *)_ptr;
  struct stack_node *nn = (struct stack_node *)malloc(sizeof(struct stack_node));
  if (NULL == nn)
    return NULL;
  nn->num = val;
  nn->next = s->top;
  s->top = nn;
  printf ("Added ->%d, addr=%p", nn->num, (s->top));
}

int pop (void *_ptr) {
  struct stack_type *st = (struct stack_type *)_ptr;
  if(empty(st))
    return -1;

  int hold = st->top->num;
  struct stack_node *temp = st->top;
  //  printf("Num = %d \n", st->top->num);
  printf ("Remov addr=%p NextPtr=%p\n", (st->top), st->top->next);
  st->top = st->top->next;
  //  printf ("Next Ptr ->%p \n",  (st->top));
  free(temp);
  return hold;
}

int empty(void *_ptr) {
  struct stack_type *st = (struct stack_type*)_ptr;
  if (st->top == NULL)
    return 1;
  else
    return 0;
}

int main () {
  printf("Stack Using Linked List! \n");
  int n;
  struct stack_type *st, s;
  st = m_init_s(&s);
  printf("Enter some integers, ending with 0\n");
  scanf("%d", &n);
  while (n != 0) {
    push(st, n);
    scanf("%d", &n);
  }
  printf("\nNumbers in reverse order\n");
  while (!empty(st))
    printf("-->[%d] ", pop(st));
  printf("\n");
}

/**
   => ./a.out
   --> 50
   --> 40
   --> 30
   --> 20
   --> 10
**/
