/*
* Aim :  LeetCode: Min Stack
* Date : June-03-2020 WednesDay
*
***/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "list.h"

struct ll_func {
  int (*compute) (void *_ptr, int);
  char key;
  char *name;
};

static int print_all_functions(void *_ptr);

struct ll_func function_table[] = {
  {
    .compute = print_all_functions,
    .key = '0',
    .name = "Print Functions",
  },
  {
    .compute = push,
    .key = '1',
    .name = "Push Element",
  },
    {
    .compute = pop,
    .key = '2',
    .name = "Pop Element",
  },
  {
    .compute = topElement,
    .key = '3',
    .name = "Top Element",
  },
  {
    .compute = isEmpty,
    .key = '4',
    .name = "Is Empty",
  },
  {
    .compute = getMin,
    .key = '5',
    .name = "Get Min",
  },
  {
    .compute = m_Display,
    .key = '7',
    .name = "Show"
  },
  {
    .compute = quit,
    .key = 'q',
    .name = "Quit",
  },
};

#define NUM_FUNCS (sizeof(function_table)/sizeof(struct ll_func))

static int print_all_functions(void *_ptr) {
  int i;
  for(i=0; i<NUM_FUNCS; i++) {
    printf ("--> Press key %c for %s\n", function_table[i].key, function_table[i].name);
  }
  return 0;
}

int main () {
  stack *sptr = NULL;
  stack s;
  int i = 0;
  char cmd[20];
  static int j = 1;

  sptr = m_init(&s, STACK_SZ);

  printf ("Welcome to simple LinkList 2.0 \n");
  printf ("===================================\n");
  print_all_functions(sptr);
  printf ("===================================\n");

  while(1) {
    printf("Enter a command to Choose Operation! \n");
    fgets(cmd, 20, stdin);

    for(i=0; i<NUM_FUNCS; i++) {
      if(function_table[i].key == cmd[0]) {
	printf ("Calling Function:-> %s \n", function_table[i].name);
	function_table[i].compute(sptr, (j++ * 20));
	break;
      }
    }
  } // while Ends
}
