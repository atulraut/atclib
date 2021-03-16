/***
    HashMap : Algorithm by Kernighan's book.
    Date : 3/10/2021
    San Diego, CA
    Ref: https://github.com/atulraut/the-practice-of-programming/blob/master/chapter-2/2.9-hash-tables/hash_tables.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

enum {
  NHASH = 16,
  MULTIPLIER = 31
};

struct nameval {
  char *name;
  int value;
  struct nameval *next;
};

struct nameval *symtab[NHASH];

/* Hash: compute hash value of string */
unsigned int get_hash(char *str) {
  unsigned int h = 0;
  unsigned char *p;
  h = 0;

  for (p = (unsigned char *)str; *p != '\0'; p++)
    h = MULTIPLIER * h + *p;

  return (h % NHASH);
}

/* lookup: Find name in symtab, with optional create */
struct nameval* lookup(char *name, int val, int isCreate) {
  struct nameval* sym = NULL;
  int h = get_hash(name);

  /* Lookup into hash Table */
  for (sym = symtab[h]; sym!= NULL; sym=sym->next)
    if (strncmp(sym->name, name, strlen(name)) == 0)
      return sym;

  if (isCreate) {
    sym = (struct nameval* )malloc(sizeof(struct nameval));
    if (NULL == sym)
      return NULL;
    /* Assume caller sends you NULL terminated string */
    sym->name = (char *)malloc(sizeof(char) * strlen(name));
    strncpy(sym->name, name, strlen(name));
    sym->value = val;
    sym->next = symtab[h];  /* Hash Table Next Pointer */
    symtab[h] = sym;
  }
  return sym;
}

void print_table () {
  for (int i=0; i < NHASH; i++) {
    struct nameval* sym = symtab[i];
    if (sym == NULL)
      continue;     /* don't print the bucket if it doesn't have anything in it! */

    debug ("symtab[%d] = ", i);
    while (sym != NULL) {
      debug ("(%s: %d)", sym->name, sym->value);
      sym = sym->next;
    }
    debug ("NULL! ");
  }
}

int main() {
  for (int i = 0; i < 42; i++) {
    char *nameBuf = (char *)malloc(sizeof(char) * 15);
    sprintf(nameBuf, "InputStr %d", i);
    //    debug ("nameBuf = %s", nameBuf);
    lookup(nameBuf, 12, 1);
  }

  print_table();
}

/**
   Exercise 2.14

   Our hash function is an excellent general-purpose hash for strings.
   Nonetheless, peculiar data might cause poor behaviour. Contruct a data set that
   causes our hash function to perform badly. Is it easier to find a bad
   set for different values of NHASH?

   Answer: My experiment was to try out URL, since that was mentioned in the book
   as possible problematic input. I tried with 8 URLs. In the beggining when NHASH
   was way bigger that the number of inputs (500 > 8), there were no collisions.
   However, when I set NHASH to something small collisions started popping.
   For NHASH=8 (the same number of inputs) there were 4 collisions. Even for NHASH=16
   (twice the number of inputs) there were 2 collisions, which was not good.
   So my guess is that input of that sort would be problematic for this algorigthm.
   And, of course, the smaller NHASH is, the bigger a possibility for collisi
**/
