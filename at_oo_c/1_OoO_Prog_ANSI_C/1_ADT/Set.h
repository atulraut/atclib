#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define debug(str,args...) printf("L=[%d] [%s] [%s] :| "str"\n", __LINE__,__FILE__, __func__, ##args)

extern const void* Set;

void* add(void* set, const void* element);
void* find(const void* set, const void* element);
void* drop(void* set, const void* element);
int contains(const void* set, const void* element);
unsigned count (const void* set);

#endif
