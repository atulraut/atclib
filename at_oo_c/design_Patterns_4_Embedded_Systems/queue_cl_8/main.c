/*
 *
 * valgrind -v --leak-check=full --show-reachable=yes ./main
 */

#include <stdio.h>
#include <stdlib.h>
#include "cachequeue.h"

struct CachedQueue *myQ;
int k = 1000;

struct q_compute {
  char  key;
  char* name;
  void (*compute) ();
};

void this_insert () {
  int h;
  myQ = CachedQueue_Create();

  for (int j=0; j<QUEUE_SIZE; j++) {
    h = myQ->baseQueue->head;
    myQ->insert(myQ,k);
    debug("inserting %d at position %d, size =%d\n",k--,h, myQ->getSize(myQ));
  };

  debug("Inserted %d elements\n",myQ->getSize(myQ));
}

void this_remove () {
  int t;
  for (int j=0;j<QUEUE_SIZE;j++) {
    t = myQ->baseQueue->tail;
    //    k = myQ->remove(myQ);
    myQ->flush(myQ);
    debug("REMOVING %d at position %d, size =%d\n",k,t, myQ->getSize(myQ));
  };
  debug("Last item removed = %d\n", k);
}

void this_display () {

}

void this_quit () {
  CachedQueue_Destroy(myQ);
  debug ("Free the Queue!");
}

void this_exit() {
  debug ("Exit Call, bbye!");
  exit(0);
}

struct q_compute func_table[] = {
  {
    .key = '1',
    .name= "Insert",
    .compute = this_insert,
  },
  {
    .key = '2',
    .name = "Remove",
    .compute = this_remove,
  },
  {
    .key = '4',
    .name = "Flush",
    .compute = CachedQueue_flush,
  },
  {
    .key = '5',
    .name = "Load",
    .compute = CachedQueue_load,
  },
  {
    .key = '6',
    .name = "DestroyC",
    .compute = this_quit,
  },
  {
    .key = '7',
    .name = "Display",
    .compute = this_display,
  },
  {
    .key = '8',
    .name = "Quit",
    .compute = this_exit
  }
};

#define NB_FUNCS (sizeof(func_table)/(sizeof(struct q_compute)))

void printf_all_functions() {
  debug ("Enter!\n");
  for(int i=0; i<NB_FUNCS; i++)
    printf ("--> Press key %c for %s \n", func_table[i].key, func_table[i].name);
}

int main(void) {
  /* test normal queue */
  //  debug("Current queue size %d\n", myQ->getSize(myQ));
  int i = 0;
  char cmd[20];
  printf ("sz-> %ld\n", NB_FUNCS);
  printf ("-> %ld %ld\n", (sizeof(func_table)), (sizeof(struct q_compute)) );

  printf ("Welcome to Simple Unix Buffer Cache Using C! \n");
  printf ("===================================");
  printf_all_functions();
  printf ("===================================\n");

  while(1) {
    printf("Enter a command \n");
    fgets(cmd, 20, stdin);

    for(i=0; i<NB_FUNCS; i++) {
      if(func_table[i].key == cmd[0]) {
	printf ("Calling command: %s \n", func_table[i].name);
	func_table[i].compute();
	break;
      }
    }
  }
  debug("End!");
  return EXIT_SUCCESS;
}
