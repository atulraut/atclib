#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cachequeue.h"

/* Constructors and Destructors:*/
void CachedQueue_Init(struct CachedQueue* const me, char* fName,
		int (*isFullfunction)(struct CachedQueue* const me),
		int (*isEmptyfunction)(struct CachedQueue* const me),
		int (*getSizefunction)(struct CachedQueue* const me),
		void (*insertfunction)(struct CachedQueue* const me, int k),
		int (*removefunction)(struct CachedQueue* const me),
		void (*flushfunction)(struct CachedQueue* const me),
		void (*loadfunction) (struct CachedQueue* const me)
		      ) {
  debug ("Enter:");
  /* Initialize base class */
  /* Below baseQueue is where new data gets Insert */
  me->baseQueue = Queue_Create();   /* Queue member must use its original functions */
  /* Initialize subclass atrirbutes */
  me->numberElementsOnDisk = 0;
  strncpy(me->filename, fName, strlen(fName));     /* Error Check */
  /* Initialize aggregates : it is where data comes from for a remove */
  me->outputQueue = Queue_Create();

  /* Initialize subclass virtual operations ptrs */
  me->isFull  = isFullfunction;
  me->isEmpty = isEmptyfunction;
  me->getSize = getSizefunction;
  me->insert  = insertfunction;
  me->remove  = removefunction;
  me->flush   = flushfunction;
  me->load    = loadfunction;
}

void CachedQueue_Cleanup(struct CachedQueue* const me) {
  Queue_Cleanup(me->baseQueue);
}

/* Operations */
int CachedQueue_isFullFunction(struct CachedQueue* const me) {
  return ((me->baseQueue->isFull(me->baseQueue)) &&
	  (me->outputQueue->isFull(me->outputQueue)));
}

int CachedQueue_isEmptyFunction(struct CachedQueue* const me) {
  return ((me->baseQueue->isEmpty(me->baseQueue)) &&
    (me->outputQueue->isEmpty(me->outputQueue)) &&
	  (me->numberElementsOnDisk == 0));
}

int CachedQueue_getSizeFunction(struct CachedQueue* const me) {
  return me->baseQueue->getSize(me->baseQueue);

  return ((me->baseQueue->getSize(me->baseQueue)) &&
    (me->outputQueue->getSize(me->outputQueue)) &&
	  (me->numberElementsOnDisk));
}

/***
 * Operation Insert(int)
 * if the Queue is Full
 *     call flush to write out th e queue to disk and reset the queue
 * end if
 * Insert the Data into the Queue
 */
void CachedQueue_insertFunction(struct CachedQueue* const me, int k) {
  debug ("Enter:");
  if (me->baseQueue->isFull(me->baseQueue)) {
    debug("Working:");
    me->baseQueue->insert(me->baseQueue, k);
    return;
  }
  debug ("Failed!!!");
}

/***
 * Operation Remove
 * if there is data in the OutputQueue
 *    remove it from the OutputQueue
 * else if there is data on disk
 *    call load to bring it into the OutputQueue
 *    remove it from the OutputQueue
 * else if there is data in the baseQueue
 *    remove it from there
 *    (if there is not data to remove then return sentinel value)
 */
int CachedQueue_removeFunction(struct CachedQueue* const me) {
  if (!me->outputQueue->isEmpty(me->outputQueue)) {
    return me->outputQueue->remove(me->outputQueue);
  } else if(me->numberElementsOnDisk > 0) {
    debug ("Enter:");
             me->load(me);
             return me->baseQueue->remove(me->baseQueue);
  } else {
    debug ("HERE!");
    return me->baseQueue->remove(me->baseQueue);
  }
}

/***
 * Operation flush
 * Precondition this is called only when Queue is Full
 *   and fileName is valid
 * Flush Algo :
 * if file is Not open, then open file
 * while not queue->isEmpty()
 *    baseQueue->remove()
 *    write data to disk
 *    numberElementsOnDisk++
 * end While
 */
void CachedQueue_flush(struct CachedQueue* const me) {
  int val = 0;
  char str[5] = {'\0'};
  FILE* fw = fopen ("CachedInDiskCopy.txt", "a+");
  // wite file I/O statements here ..
  if (!me->outputQueue->isEmpty(me->outputQueue)) {
    val = me->outputQueue->remove(me->outputQueue);
    debug ("val = %d",val);
  } else {
    val =  me->baseQueue->remove(me->baseQueue);
    sprintf(str, "%d", val);
    debug ("HERE! val = %d str = %s", val, str);
    fputs(str, fw);
    fputs("\n", fw);
  }
  fclose (fw);
}

/***
 * Operation load:
 * Precondidtion: this is called only when outputQueue is Empty
 * and fileName is valid
 * load Algo:
 * while (!outputQueue->isFull() && (nuumberElementsOndisk > 0))
 *    read from start of file (i.e. olderst datum)
 *    numberElementsOndDisk--;
 *    outputQueue=->insert()
 * end While
 */
void CachedQueue_load(struct CachedQueue* const me) {
  // write file I/o statements here..
}

struct CachedQueue* CachedQueue_Create(void) {
  struct CachedQueue *thisPtr = (struct CachedQueue*)malloc(sizeof(struct CachedQueue));

  debug ("Enter");
  if (NULL != thisPtr) {
    CachedQueue_Init(thisPtr, "CachedInDiskCopy.txt", CachedQueue_isFullFunction, CachedQueue_isEmptyFunction, CachedQueue_getSizeFunction, CachedQueue_insertFunction, CachedQueue_removeFunction,
		     CachedQueue_flush, CachedQueue_load
		     );
  } else
    return NULL;
  debug ("Returning!");
  return thisPtr;
}

void CachedQueue_Destroy(struct CachedQueue* const me) {
  if (NULL != me) {
    CachedQueue_Cleanup(me);
  }
  free (me);
}
