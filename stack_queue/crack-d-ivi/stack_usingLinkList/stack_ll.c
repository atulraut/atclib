/**
   Advanced stack implementation
   We can create number of stack using same code & track each stack
   indepedently.
   To get new stack call - m_init_s
   whatever stack we want to work on(push/pop ops) we can called.

   Author : Atul Raut
   Date : Sun Sep 22 22:59:28 2019 -0700
   Place: San Diego, CA

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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

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

struct stack_node* top(void *_ptr) {

  struct stack_type *type_obj = (struct stack_type *)_ptr;
  return type_obj->top;
}

int is_Empty(void *_ptr) {

  struct stack_type *type_obj = (struct stack_type *)_ptr;
  if (type_obj->top == NULL)
    return 1; // For stack is empty
  else
    return 0; // For Success, 0 if NOT emtpy
}


int peek(void *_ptr) {

  struct stack_type *type_obj = (struct stack_type *)_ptr;
  assert (!is_Empty(type_obj)); // Return data at the top node
  return type_obj->top->num;
}

int push(void *_ptr, int val) {

  struct stack_type *s = (struct stack_type *)_ptr;
  struct stack_node *nn = (struct stack_node *)malloc(sizeof(struct stack_node));
  if (NULL == nn)
    return -1;
  nn->num = val;
  nn->next = s->top;
  s->top = nn;
  debug ("Added ->%d, addr=%p", nn->num, (s->top));
}

int pop (void *_ptr) {

  struct stack_type *st = (struct stack_type *)_ptr;

   // Ensure the stack is not empty before popping
  //  assert(!is_Empty(type_obj) && "Stack is Empty, can't POP");
  if(is_Empty(st))
    return -1;

  int hold = st->top->num;

  struct stack_node *temp = st->top;
  //printf ("Remov addr=%p NextPtr=%p\n", (st->top), st->top->next);
  st->top = st->top->next;
  //debug ("Data = %d Next Ptr ->%p ",hold,  (st->top));
  free(temp);
  return hold;
}

void free_stack(struct stack_type* type_obj) {
  while(is_Empty(type_obj)) {
    pop(type_obj); // Pop each element, which also frees node
  }
}

void test () {
  printf("Stack Using Linked List! \n");
  int n;
  struct stack_type *stk, s;
  stk = m_init_s(&s);

    for (int i=0; i<10; ++i)
    push(stk, i);

  debug ("Top element after pushes: %d", peek(stk));

  for (int i=0; i<10; ++i)
    debug("Output = %d", pop(stk));

  /*
  printf("Enter some integers, ending with 0\n");
  scanf("%d", &n);
  while (n != 0) {
    push(st, n);
    scanf("%d", &n);
  }
  printf("\nNumbers in reverse order\n");
  while (!is_Empty(st))
    printf("-->[%d] ", pop(st));
  printf("\n");
*/
  free_stack(stk);
}

int main () {
  test ();
}

/**
   => ./a.out
   --> 50
   --> 40
   --> 30
   --> 20
   --> 10
**/
