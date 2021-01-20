#ifndef LIB_H
#define LIB_H
/*
* Aim 	 : Singaly Circular Link List.
* Author : Atul Ramesh Raut
* Date   : Saturday April 20, 2016. 10:30PM
*        : Friday Nov 01, 2019, 9.27PM
* File   : list.h
*
***/

#include <stdio.h>
#include <stdlib.h>

static struct ll_func {
  void (*compute) (void *_ptr);
  char key;
  char *name;
};

static void print_all_functions();

static void quit(void *_ptr) {
  printf ("Good Bye! \n");
  exit(0);
}

static struct ll_func function_table[] = {
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
    .compute = m_Freelist,
    .key = '4',
    .name = "Free List",
  },
  {
    .compute = m_Revlist,
    .key = '5',
    .name = "Reverse Link List",
  },
  {
    .compute = m_Display,
    .key = '7',
    .name = "Show"
  },
  {
    .compute = m_RevlistKthNode,
    .key = '8',
    .name = "Reverse K'th Node Link List",
  },
  {
    .compute = m_Sortlist,
    .key = '9',
    .name = "Sort Link List",
  },
  {
    .compute = m_ReturnNthNode_From_End,
    .key = 'a',
    .name = "Return Nth Node From End",
  },
  {
    .compute = m_RemoveDuplicateNodes,
    .key = 'b',
    .name = "Remove Duplicate Nodes",
  },
  {
    .compute = m_SearchData,
    .key = 'c',
    .name = "Search Data in Link List",
  },
  {
    .compute = quit,
    .key = 'q',
    .name = "Quit",
  },
};

#define NUM_FUNCS (sizeof(function_table)/sizeof(struct ll_func))

static int get_input(char *cmd) {
  int res = 1;

  printf ("Enter number! \n");

  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res = atoi(cmd);
    //    printf ("atoi=%d, cmd=%s \n", res, cmd);
  }
  return res;
}


static void print_all_functions() {
  int i;
  for(i=0; i<NUM_FUNCS; i++) {
    printf ("--> Press key %c for %s\n", function_table[i].key, function_table[i].name);
  }
}

static int start_ll(void *l) {
  int i = 0;
  char cmd[20];

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
	function_table[i].compute(l);
	break;
      }
    }
  } // while Ends
}

#endif
