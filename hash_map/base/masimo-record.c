/***
 * Design and implement a function that performs * input:
 * list of unordered records with timestamp, name, data * output: arranged
 * records satisfying all of below.
 * 1. Group by name
 * 2. Sort each group by timestamp in descending order
 * 3. Sort groups by timestamp
 * of the first record in desceding order example as a record in
 * format of name(timestamp) where data is not part of this example
 * Input: Foo(10), Bar(11), Kun(12), Foo(1), Bar(8), Foo(2), Bar(4), Foo(14)
 * Output:
 * Group [Foo(14), Foo(10), Foo(1)]
 * Group [Kun(12)]
 * Group [Bar(11), Bar(8), Bar(4)]
 * Takeaway :
 * @size: The size of the buffer, including the trailing null space
 * https://stackoverflow.com/questions/2674312/how-to-append-strings-using-sprintf
 * https://elixir.bootlin.com/linux/latest/source/lib/vsprintf.c#L2746
 * Date : 1-2 April 2021,
 * San Diago, CA
 * Author - Rauji(Atul) Raut.
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

struct record {
  char *name;
  int value;
  int count;
  struct record *next;
};

#define NHASH 10
#define MULTIPLIER 31
struct record *systab[NHASH];

int get_hash(char *word) {
  int h = 0, wordNum = 0;
  int w = 3;
  while (word[h] != '\0') {
    wordNum += w * word[h++];
    w = w + 2;
  }
  int loc = wordNum % NHASH + 1; //loc is assigned a value from 1 to n
  return loc;
}

int get_hash2(char *str) {
  unsigned int h = 0;
  unsigned char *p;

  for (p=(unsigned char*)str; *p != '\0'; p++)
    h = h * MULTIPLIER + *p;

  return (h % NHASH);
}

struct record* m_lookup (char *str, int val) {
  struct record *sys = NULL;
  int h = get_hash(str);

  debug("%s", str);
  for (sys=systab[h]; sys!= NULL; sys=sys->next) {
    if (strncmp(sys->name, str, strlen(sys->name)) == 0)
      return sys;
  }
}

static void swap (struct record *s, struct record *m) {
  int temp;
  temp = s->value;
  s->value = m->value;
  m->value = temp;
}

void m_sort_Record(int h) {
  struct record *sys;
  int flag = 0;
  struct record *start = systab[h];
  struct record *trav, *min;

  for(sys=systab[h]; sys->next!=NULL; sys=sys->next) {
    start  = sys;
    min = start;
    trav = start->next;
    while (trav) {
      if (min->value > trav->value) { // Ascending Order
	min = trav;
	flag = 1; // to check we really needs to swap data
      }
      trav = trav->next;
    }
    if(flag) {
      swap (start, min);
      flag = 0; // Reset the flag
    }
    start = start->next;
  }
}

/***
    Insertion Algo :
    1] Check if Str present
    2] If-1: Check if val is same or not.
    3] if-2: Val is same, dont do anything return.
    4] if-3: Val is not present, add into HashMap.
*/
struct record* m_insert (char *str, int val) {
  struct record *sys = NULL;
  struct record *sysNew = NULL;
  int h = get_hash(str);
  bool iscreate = 0;

  debug ("str = %s h = %d", str, h);
  if (NULL == systab[h]) {
    iscreate = 1;
  } else {
    /***
     * IF you reach here means, already one entry with key present.
     * Now add same key entry with different value & every time sort it.
     */
    sys = systab[h];
    sysNew = (struct record *)malloc(sizeof(struct record));
    sysNew->name = (char *)malloc(sizeof(char) * strlen(str) + 1);
    int j = snprintf(sysNew->name, strlen(str)+1, "%s\n", str);
    debug("%s j=%d", sysNew->name, j);
    sysNew->value = val;
    sys->count += 1;

    sysNew->next = sys;
    systab[h] = sysNew;
    /* Sort List in Ascending Order! */
    m_sort_Record(h);
    return sysNew;
  }

  if(iscreate) {
    sys = (struct record *)malloc(sizeof(struct record));
    sys->name = (char *)malloc(sizeof(char) * strlen(str) + 1);
    int j = snprintf(sys->name, strlen(str)+1, "%s\n", str);
    debug("%s j=%d", sys->name, j);

    sys->value = val;
    sys->count += 1;
    sys->next = systab[h];
    systab[h] = sys;
    return sys;
  }
}

void m_print_table () {
  debug("Enter !");
  for (int i=0; i < NHASH; i++) {
    struct record* sym = systab[i];
    if (sym == NULL)
      continue;     /* don't print the bucket if it doesn't have anything in it! */

    while (sym != NULL) {
      printf ("i=[%d] %s %d cnt = %d\t",i, sym->name, sym->value, sym->count);
      sym = sym->next;
    }
    printf("\n");
    //debug ("NULL! ");
  }
}

struct record** get_Record(int *col) {
  struct record* sym;
  int j = 0, i, r=0;
  /* Get Column Size */
  for (int i=0; i < NHASH; i++) {
    sym = systab[i];
    if (sym == NULL)
      continue;     /* don't print the bucket if it doesn't have anything in it! */
    j++;
  }
  debug("Enter j=%d !", j);
  *col = j;
  /* Copy Everything to Record Table */
  struct record** table = (struct record**)malloc(sizeof(struct record*) * *col);
  for (i=0; i < NHASH; i++) {
    sym = systab[i];
    if (NULL == sym)
      continue;
    table[r++] = sym;
  }
  debug("Enter *col=%d i=%d!", *col, i);
  return table;
}

/* Main routine to test input & returns result */
struct record** m_makeRecord(struct record *rt, int sz, int *col) {

  /* Inser & Sort */
  for (int i=0; i<sz; i++) {
    m_insert(rt[i].name, rt[i].value);
  }
  debug("");
  /* Return in order user Ask */
  struct record**result = get_Record(col);
  return result;
}

void test_record() {
  int col;
  int sz = 8;
  /* Input : Foo(10), Bar(11), Kun(12), Foo(1), Bar(8), Foo(2), Bar(4), Foo(14) */
  struct record rt[sz];
  rt[0] = (struct record) {.name = "Foo", .value=10, .next=NULL};
  rt[1] = (struct record) {.name = "Bar", .value=11, .next=NULL};
  rt[2] = (struct record) {.name = "Kun", .value=12, .next=NULL};
  rt[3] = (struct record) {.name = "Foo", .value=1,  .next=NULL};
  rt[4] = (struct record) {.name = "Bar", .value=8,  .next=NULL};
  rt[5] = (struct record) {.name = "Foo", .value=2,  .next=NULL};
  rt[6] = (struct record) {.name = "Bar", .value=4,  .next=NULL};
  rt[7] = (struct record) {.name = "Foo", .value=14, .next=NULL};

  struct record** result = m_makeRecord(rt, sz, &col);

  debug ("Enter");
  for (int i=0; i<col; i++) {
    struct record* sym = result[i];
    while (sym != NULL) {
      printf ("i=[%d] %s %d cnt = %d\t",i, sym->name, sym->value, sym->count);
      sym = sym->next;
    }
    printf("\n");
  }
}

int main () {
  test_record();
  m_print_table();
}

/**
   => ./a.out
   [m_insert] L=122 :str = Foo h = 3
   [m_insert] L=149 :Foo j=4
   [m_insert] L=122 :str = Bar h = 2
   [m_insert] L=149 :Bar j=4
   [m_insert] L=122 :str = Kun h = 1
   [m_insert] L=149 :Kun j=4
   [m_insert] L=122 :str = Foo h = 3
   [m_insert] L=134 :Foo j=4
   [m_insert] L=122 :str = Bar h = 2
   [m_insert] L=134 :Bar j=4
   [m_insert] L=122 :str = Foo h = 3
   [m_insert] L=134 :Foo j=4
   [m_insert] L=122 :str = Bar h = 2
   [m_insert] L=134 :Bar j=4
   [m_insert] L=122 :str = Foo h = 3
   [m_insert] L=134 :Foo j=4
   [m_makeRecord] L=206 :
   [get_Record] L=185 :Enter j=3 !
   [get_Record] L=195 :Enter *col=3 i=10!
   [test_record] L=228 :Enter
   i=[0] Kun 12 cnt = 1	
   i=[1] Bar 4 cnt = 0	i=[1] Bar 8 cnt = 1	i=[1] Bar 11 cnt = 2	
   i=[2] Foo 1 cnt = 0	i=[2] Foo 2 cnt = 1	i=[2] Foo 10 cnt = 1	i=[2] Foo 14 cnt = 2	
   [m_print_table] L=160 :Enter !
   i=[1] Kun 12 cnt = 1	
   i=[2] Bar 4 cnt = 0	i=[2] Bar 8 cnt = 1	i=[2] Bar 11 cnt = 2	
   i=[3] Foo 1 cnt = 0	i=[3] Foo 2 cnt = 1	i=[3] Foo 10 cnt = 1	i=[3] Foo 14 cnt = 2	
**/
