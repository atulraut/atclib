/***
    शिवजयंती!

    Ch-1 : ADT Information hiding.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed 19 Feb 2025 03:53:52 PM PST
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

#include "new.h"
#include "Set.h"
#include "Object.h"

struct Set {
  unsigned count;
};

struct Object {
  unsigned count;
  struct Set* in;
};

static const size_t _Set = sizeof(struct Set);
static const size_t _Object = sizeof(struct Object);

const void* Set = &_Set;
const void* Object = &_Object;

void* new(const void* type, ...) {

  const size_t size = *(const size_t *)type;
  void* p = calloc(1, size);

  assert(p);

  debug("p->[%pK]", p);
  return p;
}

void delete(void *item) {
  free(item);
}

void *add(void* _set, const void* _element) {
  struct Set* set = _set;
  struct Object* element = (void *)_element;

  assert(set);
  assert(element);

  if(!element->in)
    element->in = set;
  else
    assert(element->in == set);

  ++element->count;
  ++set->count;

  debug("element->count->[%d] set->count->[%d]", element->count, set->count);
  return element;
}

void* find (const void* _set, const void* _element) {

  const struct Object* element = _element;

  assert(_set);
  assert(element);

  return element->in == _set ? (void*)element : 0;

}

int contains (const void* _set, const void* _element) {
  debug ("Enter ->");
  return find(_set, _element) !=0;
}

void* drop (void* _set, const void* _element) {

  debug ("Enter ->");
  struct Set* set = _set;
  struct Object* element = find(set, _element);

  if(element) {
    if(--element->count ==0)
      element->in = 0;
    --set->count;
  }
  return element;
}

unsigned count (const void * _set) {

  debug ("Enter ->");
  const struct Set* set = _set;
  assert(set);
  return set->count;
}

int differ (const void* a, const void* b) {
  debug ("Enter ->");
  return a != b;
}
