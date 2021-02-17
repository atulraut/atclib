/*
* Aim :  Create Singly Link List
* Date : July-29-2016
*
***/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "list.h"

struct ll_func {
  void (*compute) (void *_ptr);
  char key;
  char *name;
};

static void print_all_functions();

struct ll_func function_table[] = {
  {
    .compute = print_all_functions,
    .key = '0',
    .name = "Print Functions",
  },
  {
    .compute = m_Addfirst,
    .key = '1',
    .name = "Add First",
  },
  {
    .compute = m_set_random_ptr,
    .key = '2',
    .name = "Set Random",
  },
  {
    .compute = m_copyRandomList,
    .key = '3',
    .name = "Copy List with Random Pointer",
  },
  {
    .compute = m_Display,
    .key = '7',
    .name = "Show"
  },
  {
    .compute = quit,
    .key = 'q',
    .name = "Quit !",
  },
};

#define NUM_FUNCS (sizeof(function_table)/sizeof(struct ll_func))

static void print_all_functions() {
  int i;
  for(i=0; i<NUM_FUNCS; i++) {
    printf ("--> Press key %c for %s\n", function_table[i].key, function_table[i].name);
  }
}

int main () {
  int i = 0;
  char cmd[20];

  //head = m_Init(head);

  printf ("Welcome to simple LinkList 2.0 \n");
  printf ("===================================\n");
  print_all_functions();
  printf ("===================================\n");

  while(1) {
    printf("Enter a command \n");
    fgets(cmd, 20, stdin);

    for(i=0; i<NUM_FUNCS; i++) {
      if(function_table[i].key == cmd[0]) {
	printf ("Calling command: %s \n", function_table[i].name);
	function_table[i].compute(head);
	break;
      }
    }
  } // while Ends
}
