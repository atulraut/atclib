/***

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri 27 Sep 2024 06:29:56 PM PDT
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

#define	ENOSPC		-1	/* No space left on device */

#define SMP_CACHE_BYTES (1 << 5)

struct ptr_ring {
  int producer;
  //  spinlock_t producer_lock;
  int consumer_head; /* next valid entry */
  int consumer_tail; /* next entry to invalidate */
  //  spinlock_t consumer_lock;
  /* Shared consumer/producer data */
  /* Read-only by both the producer and the consumer */
  int size; /* max entries in queue */
  int batch; /* number of entries to consume in a batch */
  void **queue;
};

bool __ptr_ring_full (struct ptr_ring *r) {
  return r->queue[r->producer];
}
/*
boll ptr_ring_full(struct ptr_ring *r) {
  bool ret;

  spin_lock(&r->producer_lock);
  ret =  __ptr_ring_full(r);
  spin_ulock_irq(&r->producer_lock);

  return ret;
}*/

bool ptr_ring_full(struct ptr_ring *r) {
  unsigned long flags;
  bool ret;

  // spin_lock_irqsave(&r->producer_lock, flags);
  ret = __ptr_ring_full(r);
  // spin_unlock_irqrestore(&r->producer_lock, flags);

  return ret;
}

int __ptr_ring_produce(struct ptr_ring *r, void *ptr) {
  if (!r->size || r->queue[r->producer])
    return ENOSPC;

  //  smp_wmb();
  r->queue[r->producer++] = ptr;

  //  memcpy((void *)p, (const void *)res, size);
  if (r->producer >= r->size)
    r->producer = 0;

  return 0;
}

static inline int ptr_ring_produce(struct ptr_ring *r, void *ptr) {
  int ret;

  //  spin_lock(&r->producer_lock);
  ret = __ptr_ring_produce(r, ptr);
  //  spin_unlock(&r->producer_lock);

  return ret;
}

/*
int ptr_ring_produce_any(struct ptr_ring *r, void *ptr) {
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&r->producer_lock, flags);
	ret = __ptr_ring_produce(r, ptr);
	spin_unlock_irqrestore(&r->producer_lock, flags);

	return ret;
} */

void* __ptr_ring_peek(struct ptr_ring *r) {
  if (r->size)
    return r->queue[r->consumer_head];
  return NULL;
}

bool __ptr_ring_empty(struct ptr_ring *r) {
  if (r->size) {
    //debug ("r->consumer_head = [%d]", r->consumer_head);
    return !r->queue[r->consumer_head];
  }
  return true;
}

bool ptr_ring_empty(struct ptr_ring *r) {
	bool ret;

	//	spin_lock(&r->consumer_lock);
	ret = __ptr_ring_empty(r);
	//	spin_unlock(&r->consumer_lock);

	return ret;
}
/*
static inline bool ptr_ring_empty_irq(struct ptr_ring *r)
{
	bool ret;

	spin_lock_irq(&r->consumer_lock);
	ret = __ptr_ring_empty(r);
	spin_unlock_irq(&r->consumer_lock);

	return ret;
}
*/

 // get one element - remove
void __ptr_ring_discard_one(struct ptr_ring *r) {
  int consumer_head = r->consumer_head;
  int head = consumer_head++;

  //debug ("r->consumer_head = [%d]", r->consumer_head);
  //debug ("r->consumer_tail = [%d]", r->consumer_tail);

  if (consumer_head - r->consumer_tail >= r->batch
    || consumer_head >= r->size) {

    while (head >= r->consumer_tail)
      r->queue[head--] = NULL;
    r->consumer_tail = consumer_head;
  }

  if (consumer_head >= r->size) {
    consumer_head = 0;
    r->consumer_tail = 0;
  }

  r->consumer_head = consumer_head;
  debug ("r->consumer_head = [%d]", r->consumer_head);
  debug ("r->consumer_tail = [%d]", r->consumer_tail);
}

void* __ptr_ring_consume(struct ptr_ring *r) {
  void *ptr;

  ptr = __ptr_ring_peek(r);
  if (ptr)
    __ptr_ring_discard_one(r);

  return ptr;
}

int __ptr_ring_consume_batched(struct ptr_ring *r, void **array, int n) {
  void* ptr;
  int i;

  for (int i=0; i<n; ++i) {
    ptr = __ptr_ring_consume(r);
    if(!ptr)
      break;
    array[i] = ptr;
  }
  return i;
}

/*
  static inline void *ptr_ring_consume_any(struct ptr_ring *r) {
  unsigned long flags;
  void *ptr;

  spin_lock_irqsave(&r->consumer_lock, flags);
  ptr = __ptr_ring_consume(r);
  spin_unlock_irqrestore(&r->consumer_lock, flags);

  return ptr;
  }

*/
void *ptr_ring_consume(struct ptr_ring *r) {
  void *ptr;

  //  spin_lock(&r->consumer_lock);
  ptr = __ptr_ring_consume(r);
  //  spin_unlock(&r->consumer_lock);

  return ptr;
}



int ptr_ring_consume_batched(struct ptr_ring *r,
			   void **array, int n) {
  int ret;

  //  spin_lock(&r->consumer_lock);
  ret = __ptr_ring_consume_batched(r, array, n);
  //spin_unlock(&r->consumer_lock);

  return ret;
}

void **__ptr_ring_init_queue_alloc_noprof(unsigned int size/*, gfp_t gfp*/) {
  if (size > /*KMALLOC_MAX_SIZE */ sizeof(void *))
    return NULL;
  return malloc(sizeof(void *));
  //return kvmalloc_array_noprof(size, sizeof(void *)/*, gfp | __GFP_ZERO*/);
}


void __ptr_ring_set_size(struct ptr_ring *r, int size) {
  r->size = size;
  r->batch = r->batch = SMP_CACHE_BYTES * 2 / sizeof(*(r->queue));

  if (r->batch > r->size/2 || !r->batch)
    r->batch = 1;
}

int ptr_ring_init(struct ptr_ring *r, int size/*, gfp_t gfp*/) {
  r->queue = __ptr_ring_init_queue_alloc_noprof(size/*, gfp*/);
  if (!r->queue)
    return -1; // -ENOMEM
  __ptr_ring_set_size(r, size);
  r->producer = r->consumer_head = r->consumer_tail = 0;
  // spin_lock_init(&r->producer_lock);
  // spin_lock_init(&r->consumer_lock);

  return 0;
}

void ptr_ring_unconsume (struct ptr_ring *r, void **batch, int n,
			 void(*destroy)(void *)) {
  unsigned long flag;
  int head;

  //spin_lock_irqsave(&r->consumer_lock, flags);
  //spin_lock(&r->producer_lock);

  if(!r->size)
    goto done;

  head = r->consumer_head - 1;
  while (head >= r->consumer_tail)
    r->queue[head--] = NULL;

  r->consumer_tail = r->consumer_head;

  while(n) {
    head = r->consumer_head - 1;
    if(head < 0)
      head = r->size - 1;
    if (r->queue[head]) {
      goto done;
    }
    r->queue[head] = batch[--n];
    r->consumer_tail = head;
    r->consumer_head = head; // FixMe
  }

 done:
  while(n)
    destroy(batch[--n]);
  //spink_unlock(&r->producer_lock);
  //spin_unlock_irqrestore(&r->consumer_lock, flags);
}

void ptr_ring_cleanup(struct ptr_ring *r, void(*destroy)(void *)) {
  void *ptr;
  if(destroy)
    while(ptr = ptr_ring_consume(r))
      destroy(ptr);
  free(r->queue);
}

/**

 **/
