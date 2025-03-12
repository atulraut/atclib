#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern const void* Object; /* net(Object); */

int differ(const void* a, const void* b);

#endif
