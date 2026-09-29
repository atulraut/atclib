/**

   Implement reference counting

   Date: Tue Sep 29 14:11:49 PDT 2026
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int refcount;
  int data;
} Object;

Object *object_create(int data) {
  Object *obj = malloc(sizeof(*obj));

  if (obj == NULL)
    return NULL;

  obj->refcount = 1;
  obj->data = data;

  return obj;
}

Object *object_get(Object *obj) {
  if (obj == NULL)
    return NULL;

  obj->refcount++;

  return obj;
}

void object_put(Object *obj) {
  if (obj == NULL)
    return;

  obj->refcount--;

  if (obj->refcount == 0) {
    printf("Destroying object\n");
    free(obj);
  }
}

int main(void) {
  Object *a = object_create(100);

  if (a == NULL)
    return 1;

  printf("refcount = %d\n", a->refcount);   // 1
  Object *b = object_get(a);
  printf("refcount = %d\n", a->refcount);   // 2
  object_put(b);
  printf("refcount = %d\n", a->refcount);   // 1
  object_put(a);                            // 0 -> free

  return 0;
}

/**
   refcount = 1
   refcount = 2
   refcount = 1
   Destroying object
**/
