#ifndef CACHEQUEUE_H_

#define CACHEQUEUE_H_

#include "queue.h"

/* Derived Class Queue */
struct CachedQueue {
  struct Queue *baseQueue;   /* Base Class */
  /* new attribute */
  char filename[80];

  int numberElementsOnDisk;
  /* Aggregation in Subclass */
  struct Queue *outputQueue;

  /* Inherited Virtual Functions */
  int (*isFull)(struct CachedQueue* const me);
  int (*isEmpty)(struct CachedQueue* const me);
  int (*getSize)(struct CachedQueue* const me);
  void (*insert)(struct CachedQueue* const me, int k);
  int (*remove)(struct CachedQueue* const me);

  /* New Virtual Functions */
  void (*flush)(struct CachedQueue* const me);
  void (*load) (struct CachedQueue* const me);
};

/* Constructors and Destructors:*/
void CachedQueue_Init(struct CachedQueue* const me, char* fileName,
		int (*isFullfunction)(struct CachedQueue* const me),
		int (*isEmptyfunction)(struct CachedQueue* const me),
		int (*getSizefunction)(struct CachedQueue* const me),
		void (*insertfunction)(struct CachedQueue* const me, int k),
		int (*removefunction)(struct CachedQueue* const me),
		void (*flushfunction)(struct CachedQueue* const me),
		void (*loadfunction) (struct CachedQueue* const me)
	      );

void CachedQueue_Cleanup(struct CachedQueue* const me);

/* Operations */
int CachedQueue_isFullFunction(struct CachedQueue* const me);
int CachedQueue_isEmptyFunction(struct CachedQueue* const me);
int CachedQueue_getSizeFunction(struct CachedQueue* const me);
void CachedQueue_insertFunction(struct CachedQueue* const me, int k);
int CachedQueue_removeFunction(struct CachedQueue* const me);
void CachedQueue_flush(struct CachedQueue* const me);
void CachedQueue_load(struct CachedQueue* const me);

struct CachedQueue * CachedQueue_Create(void);
void CachedQueue_Destroy(struct CachedQueue* const me);

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#endif /*CACHEQUEUE_H_*/
