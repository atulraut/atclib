#include <stdio.h>
#include "../at_lib.h"

// Alignment requirements
// (typical 32 bit machine)

// char         1 byte
// short int    2 bytes
// int          4 bytes
// double       8 bytes

/***
     Code I :
     Ref : https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/
*/
// structure A
typedef struct structa_tag {
  char        c;
  short int   s;
} structa_t;

// structure B
typedef struct structb_tag {
  short int   s;
  char        c;
  int         i;
} structb_t;

// structure C
typedef struct structc_tag {
  char        c;
  double      d;
  int         s;
} structc_t;

// structure D
typedef struct structd_tag {
  double      d;
  int         s;
  char        c;
} structd_t;

/***
    Code II :
    Ref : https://stackoverflow.com/questions/4306186/structure-padding-and-packing
 */
// size is 8, 4 + 1, then round to multiple of 4 (int's size),
struct stu_a {
  int i;
  char c;
};

// size is 16, 8 + 1, then round to multiple of 8 (long's size),
struct stu_b {
  long l;
  char c;
};

// size is 24, l need padding by 4 before it, then round to multiple of 8 (long's size),
struct stu_c {
  int i;
  long l;
  char c;
};

// size is 16, 8 + 4 + 1, then round to multiple of 8 (long's size),
struct stu_d {
  long l;
  int i;
  char c;
};

// size is 16, 8 + 4 + 1, then round to multiple of 8 (double's size),
struct stu_e {
  double d;
  int i;
  char c;
};

// size is 24, d need align to 8, then round to multiple of 8 (double's size),
struct stu_f {
  int i;
  double d;
  char c;
};

// size is 4,
struct stu_g {
  int i;
};

// size is 8,
struct stu_h {
  long l;
};

// test - padding within a single struct,
int test_struct_padding() {
  printf("%s: %ld\n", "stu_a", sizeof(struct stu_a));
  printf("%s: %ld\n", "stu_b", sizeof(struct stu_b));
  printf("%s: %ld\n", "stu_c", sizeof(struct stu_c));
  printf("%s: %ld\n", "stu_d", sizeof(struct stu_d));
  printf("%s: %ld\n", "stu_e", sizeof(struct stu_e));
  printf("%s: %ld\n", "stu_f", sizeof(struct stu_f));

  printf("%s: %ld\n", "stu_g", sizeof(struct stu_g));
  printf("%s: %ld\n", "stu_h", sizeof(struct stu_h));

  return 0;
}

// test - address of struct,
int test_struct_address() {
  printf("%s: %ld\n", "stu_g", sizeof(struct stu_g));
  printf("%s: %ld\n", "stu_h", sizeof(struct stu_h));
  printf("%s: %ld\n", "stu_f", sizeof(struct stu_f));

  struct stu_g g;
  struct stu_h h;
  struct stu_f f1;
  struct stu_f f2;
  int x = 1;
  long y = 1;

  printf("address of %s: %p\n", "g", &g);
  printf("address of %s: %p\n", "h", &h);
  printf("address of %s: %p\n", "f1", &f1);
  printf("address of %s: %p\n", "f2", &f2);
  printf("address of %s: %p\n", "x", &x);
  printf("address of %s: %p\n", "y", &y);

  // g is only 4 bytes itself, but distance to next struct is 16 bytes(on 64 bit system) or 8 bytes(on 32 bit system),
  printf("space between %s and %s: %ld\n", "g", "h", (long)(&h) - (long)(&g));

  // h is only 8 bytes itself, but distance to next struct is 16 bytes(on 64 bit system) or 8 bytes(on 32 bit system),
  printf("space between %s and %s: %ld\n", "h", "f1", (long)(&f1) - (long)(&h));

  // f1 is only 24 bytes itself, but distance to next struct is 32 bytes(on 64 bit system) or 24 bytes(on 32 bit system),
  printf("space between %s and %s: %ld\n", "f1", "f2", (long)(&f2) - (long)(&f1));

  // x is not a struct, and it reuse those empty space between struts, which exists due to padding, e.g between g & h,
  printf("space between %s and %s: %ld\n", "x", "f2", (long)(&x) - (long)(&f2));
  printf("space between %s and %s: %ld\n", "g", "x", (long)(&x) - (long)(&g));

  // y is not a struct, and it reuse those empty space between struts, which exists due to padding, e.g between h & f1,
  printf("space between %s and %s: %ld\n", "x", "y", (long)(&y) - (long)(&x));
  printf("space between %s and %s: %ld\n", "h", "y", (long)(&y) - (long)(&h));

  return 0;
}

int main() {
  /* Code I : */
  debug ("sizeof(structa_t) = %lu\n", sizeof(structa_t)); // 4
  debug ("sizeof(structb_t) = %lu\n", sizeof(structb_t)); // 8
  debug ("sizeof(structc_t) = %lu\n", sizeof(structc_t)); // 24
  debug ("sizeof(structd_t) = %lu\n", sizeof(structd_t)); // 16
  /* Code II : */
  test_struct_padding();
  /* Code III : */
  test_struct_address();

  return 0;
}

/**
   // Coe I :
   => ./a.out
   [main] L=40 :sizeof(structa_t) = 4

   [main] L=41 :sizeof(structb_t) = 8

   [main] L=42 :sizeof(structc_t) = 24

   [main] L=43 :sizeof(structd_t) = 16

   // Code II :
   stu_a: 8
   stu_b: 16
   stu_c: 24
   stu_d: 16
   stu_e: 16
   stu_f: 24
   stu_g: 4
   stu_h: 8

   // Code III :
   address of g: 0x7ffe28830f90
   address of h: 0x7ffe28830fa0
   address of f1: 0x7ffe28830fb0
   address of f2: 0x7ffe28830fd0
   address of x: 0x7ffe28830f9c
   address of y: 0x7ffe28830fa8
   space between g and h: 16
   space between h and f1: 16
   space between f1 and f2: 32
   space between x and f2: -52
   space between g and x: 12
   space between x and y: 12
   space between h and y: 8
**/
