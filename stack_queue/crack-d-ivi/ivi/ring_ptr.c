#include <stdio.h>
#include <stdlib.h>
#include "ring_ptr.h"

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

struct tap_queue;

struct tap_queue {
  struct ptr_ring ring;
};


void test () {
  struct tap_queue *q;
  q = (struct tap_queue *)malloc (sizeof(struct tap_queue));

  ptr_ring_init(&q->ring, 5);

  // Producer
  ptr_ring_produce(&q->ring, "Atul-1");
  //  if (!ptr_ring_empty(&q->ring)) {
  ptr_ring_produce(&q->ring, "Atul-2");
  ptr_ring_produce(&q->ring, "Atul-3");
  ptr_ring_produce(&q->ring, "Atul-4");
  ptr_ring_produce(&q->ring, "Atul-5");
  ptr_ring_produce(&q->ring, "Atul-6");
  //  }

  debug ("Q size = %d", *(&q->ring.size) );
  // Consumer
  //for (int i=0; i<*(&q->ring.size); ++i) {
  while (!ptr_ring_empty(&q->ring)) {
    char* str = (char *)ptr_ring_consume(&q->ring);
    debug ("str = [%s]", str);
  }
  //  ptr_ring_cleanup(&q->ring, __skb_array_destroy_skb);
}


int main () {
  test();
}
