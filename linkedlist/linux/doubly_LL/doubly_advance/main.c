#include "list.h"
#include "atlist.h"

struct doublyLL_func {
  char key;
  char* name;
  void (*compute)();
};

struct doublyLL_func func_linkLL_stat[] = {
  {
    .key     = '1',
    .name    = "List-I",
    .compute = make_DoublyLL,
  },
  {
    .key     = '7',
    .name    = "Quit",
    .compute = quit,
  },
  {
    .key     = '8',
    .name    = "Display",
    .compute = Display,
  },
};

#define NB_FUNCS (sizeof(func_linkLL_stat)/sizeof(struct doublyLL_func))

void printf_all_functions() {
  for(int i=0; i<NB_FUNCS; i++)
    printf ("--> Press key %c for %s \n", func_linkLL_stat[i].key, func_linkLL_stat[i].name);
}

int main() {
  int i = 0;
  char cmd[20];
  printf ("\n\nsz-> %ld\n", NB_FUNCS);

   printf ("Welcome to Doubly Linked List Using Linux 1.0 \n");
  printf ("===================================\n");
  printf_all_functions();
  printf ("===================================\n");

  while(true) {
    printf ("Enter an Command! \n");
    fgets(cmd, 20, stdin);

    for(i=0; i<NB_FUNCS; ++i) {
      printf ("Calling Command: %s \n", func_linkLL_stat[i].name);
      if (func_linkLL_stat[i].key == cmd[0]) {
	func_linkLL_stat[i].compute();
	break;
      }
    }
  }
  return 0;
}
