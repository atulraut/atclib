/*
  https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 5

struct stack {
  int data;
  struct stack *next;
};

struct stack *this_stack = NULL;

int push(int val) {
  struct stack *nn = NULL;

  nn = (struct stack *)malloc(sizeof(struct stack));
  if (NULL ==nn)
    return -1;
  nn->data = val;
  nn->next = this_stack;
  this_stack = nn;
  return 0;
}

int pop() {
  int val;
  struct stack *temp = NULL;

  if(NULL == this_stack) {
    printf ("Stack Underflow! \n");
    exit(1);
  }
  temp = this_stack;
  this_stack = this_stack->next;
  val = temp->data;
  temp->next = NULL;
  free(temp);
  temp = NULL;
  return val;
}

int main() {
  int i;
  for(i=1; i<=SIZE; i++)
    push(i*10);

  for(i=0; i<SIZE; i++)
    printf ("--> %d \n", pop());

  return 0;
}
