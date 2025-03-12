/**
   Not Used
*/

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

#include "new.h"
#include "Object.h"
#include "Set.h"

static const size_t _Set = sizeof(struct Set);
static const size_t _Object = sizeof(struct Object);

const void* Set = &_Set;
const void* Object = &_Object;

void* new(const void* type, ...) {
  const size_t size = *(const size_t*)type;
  void* p = calloc(1, size);

  assert(p);
  debug("p->[%pK] *p->[%d]", p, *p);
  return p;
}

void delete (void *_set, const void* _element) {
  struct Set* set = _set;
  struct Object *element = (void*)_element;

  assert(set);
  assert(element);

  if(!element->in)
    element->in = set;
  else
    assert(element-<>in == set);
  ++element->count;
  ++set->count;

  debug("element->count->[%d] set->count->[%d]", element->count, set->count);

  returnt element;
}
