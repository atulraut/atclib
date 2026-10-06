/***
 * Stack Implementation using a Linked List!
 * Tue 05 Nov 2024 03:48:19 PM PST
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct node {
  int data;
  struct node* next;
};

struct stack {
  struct node* top;
};

void init_stack(struct stack *st_obj) {
  st_obj->top = NULL;
}

/**
  Returns 1 if the top of the stack is NULL (indicating stack is empty),
  and 0 otherwise
*/
int is_empty(struct stack* st_obj) {
  return st_obj->top == NULL;
}

void push(struct stack *st_obj, int val) {
  struct node* nn = (struct node *)malloc(sizeof(struct node));
  assert(nn != NULL && "Memory allocation failed.");

  nn->data = val;
  nn->next = st_obj->top;
  st_obj->top = nn;
}

int pop(struct stack* st_obj ) {
  assert(!is_empty(st_obj) && "Stack is Empty, cant pop");

  struct node* tmp_st_obj = st_obj->top;
  int data = tmp_st_obj->data;
  st_obj->top = st_obj->top->next;
  free(tmp_st_obj);

  return data;
}

int peek (struct stack* st_obj) {
  assert(!is_empty(st_obj) && "Cant peek an empty stack.");
  return st_obj->top->data;
}

void free_stack(struct stack* st_obj) {
  while (!is_empty(st_obj))
    pop(st_obj);
}

int main () {
  struct stack st_obj;
  init_stack(&st_obj);

  push(&st_obj, 10);
  push(&st_obj, 20);
  push(&st_obj, 30);

  debug ("Top Element after pushes: %d", peek(&st_obj));
  debug("Popped Element: %d", pop(&st_obj));
  debug("Popped Element: %d", pop(&st_obj));
  debug ("Top Element after pushes: %d", peek(&st_obj));
  debug ("Top Element after pushes: %d", peek(&st_obj));
  debug("Popped Element: %d", pop(&st_obj));
  debug ("Top Element after pushes: %d", peek(&st_obj));
  //free(&st_obj);
  return 0;
}
