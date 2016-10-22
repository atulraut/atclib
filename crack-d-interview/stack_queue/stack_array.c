/***
* Aim : Implementstack using static array.
* Date : Wednesday, Oct 19 2016, 08:00 AM
* File : main.c
* S->[LIFO] : Last In First Out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
int top = -1;
int stack[MAX];
int m_push(int val);
int m_pop ();
int m_topElement();
int m_isEmpty();

int main () {
  int a;
  m_push(10);
  printf("\n[m_push] Value inserted = 10");
  m_push(20);
  printf("\n[m_push] Value inserted = 20");
  m_push(30);
  printf("\n[m_push] Value inserted = 30");
  a = m_pop();
  printf("\n[m_pop] The poped element is %d \n",a);
  m_isEmpty();
  a = m_pop();
  printf("\n[m_pop] The poped element is %d \n",a);
  a = m_topElement();
  printf("\n[m_topElement] Top element is %d \n",a);
  a = m_pop();
  printf("\n[m_pop] The poped element is %d \n",a);
  m_isEmpty();
  a = m_pop();
  printf("\n[m_pop] The poped element is %d \n",a);
}

int m_push(int val) {
  if (top == MAX-1)
    return -1;
  top++;
  stack[top] = val;
  printf ("\n[push] top=%d", top);
}

int m_pop () {
  int val;
  if (top < 0)
    return -1;
  val = stack[top];
  top = top-1;
  printf ("\n[pop] top=%d", top);
  return val;
}

int m_topElement() {
  if (top < 0)
    return -1;
  return stack[top];
}

int m_isEmpty() {
  if(top < 0)
    printf ("[isEmpty] Empty S - top=%d", top);
  else
    printf ("[isEmpty] Not - top=%d", top);  
}
