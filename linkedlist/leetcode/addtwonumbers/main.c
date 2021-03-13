/*
* Aim :  Create Singly Link List
* Date : July-29-2016
* Date : Feb - 13-02-2021 San Diego, CA
* Date : March - 11-03-2021 San Diego, CA
* FixMed - Pending
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
    .compute = m_Addlast,
    .key = '2',
    .name = "Add Last",
  },
  {
    .compute = m_Delfirst,
    .key = '3',
    .name = "Delete First",
  },
  {
    .compute = middleNode,
    .key = '4',
    .name = "LeetCode: middle Node",
  },
  {
    .compute = m_Freelist,
    .key = '5',
    .name = "Free List",
  },
  {
    .compute = m_Display,
    .key = '7',
    .name = "Show"
  },
  {
    .compute = m_Sortlist,
    .key = '9',
    .name = "Sort Link List",
  },
  {
    .compute = m_addTwoNumbers,
    .key = 'd',
    .name = "Add Two Int of different Linked List",
  },
  {
    .compute = m_mergeTwoLinkedList,
    .key = 'm',
    .name = "Merged 2 Linked List",
  },

  {
    .compute = m_sortedMergeLL,
    .key = 'n',
    .name = "Merged 2 Sorted Linked List",
  },
   {
    .compute = m_setLLType,
    .key = 's',
    .name = "Switched Linked List- L1 : L2 ?",
  },
  {
    .compute = m_quit,
    .key = 'q',
    .name = "Quit",
  },
};

#define NUM_FUNCS (sizeof(function_table)/sizeof(struct ll_func))

static void print_all_functions() {
  int i;
  for(i=0; i<NUM_FUNCS; i++) {
    printf ("--> Press key %c for %s\n", function_table[i].key, function_table[i].name);
  }
}

void motion_linkedlist (void *_ptr) {
  int i = 0;
  char cmd[20];

  struct list *list = (struct list *)_ptr;

  printf ("Welcome to simple LinkList 3.0 \n");
  printf ("===================================\n");
  print_all_functions();
  printf ("===================================\n");

  while(1) {
    printf("Enter a command \n");
    fgets(cmd, 20, stdin);

    for(i=0; i<NUM_FUNCS; i++) {
      if(function_table[i].key == cmd[0]) {
	printf ("Calling command: %s \n", function_table[i].name);
	function_table[i].compute(list);
	break;
      }
    }
  } // while Ends
}

/* Set Linked List Type- (L1 : L2) ? */
void m_setLLType() {
  int llType = 0;
  int cmd;

  while (1) {
    printf ("Select Linked List Type ? 1 : 2 \n");
    scanf ("%d", &cmd);
    llType = cmd;
    printf ("llType = %d, cmd = %d \n", llType, cmd);
    if (llType == 1)
      l_base = list1;
    if (llType == 2)
      l_base = list2;

    debug ("Selected Linked List Type l=%p L1=%p L2=%p\n", l_base, list1, list2);

    motion_linkedlist (l_base);
  }
}

int main () {
  struct list ll1, ll2;

  list1 = m_Init(&ll1);
  list2 = m_Init(&ll2);
  debug ("Linked List Ptrs l=%p L1=%p L2=%p", l_base, list1, list2);

  m_setLLType ();
}
