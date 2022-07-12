/*
 *
 * valgrind -v --leak-check=full --show-reachable=yes ./main
 */

#include <stdio.h>
#include <stdlib.h>
#include "cachequeue.h"

int main(void) {
  int j,k, h, t;

  debug ("Enter");
  /* test normal queue */
  struct CachedQueue *myQ;
  myQ = CachedQueue_Create();
  k = 1000;
  for (j=0; j<QUEUE_SIZE; j++) {
    h = myQ->baseQueue->head;
    myQ->insert(myQ,k);
    debug("inserting %d at position %d, size =%d\n",k--,h, myQ->getSize(myQ));
  };

  debug("Inserted %d elements\n",myQ->getSize(myQ));
  for (j=0;j<QUEUE_SIZE;j++) {
    t = myQ->baseQueue->tail;
    k = myQ->remove(myQ);
    debug("REMOVING %d at position %d, size =%d\n",k,t, myQ->getSize(myQ));
  };
  debug("Last item removed = %d\n", k);
  debug("Current queue size %d\n", myQ->getSize(myQ));
  CachedQueue_Destroy(myQ);
  puts("Queue test program");
  debug("End!");
  return EXIT_SUCCESS;
}
