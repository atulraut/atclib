/***
    What is the 8 queens problem? Write a C program to solve it.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 24 Oct 2021
    Fair Oaks, CA.
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
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

static int t[10]={-1};
void queens(int i);
int empty(int i);
void print_solution();

void queens(int i) {
  for(t[i]=1;t[i]<=8;t[i]++) {
    if(empty(i)) {
      if(i==8) {
	print_solution();
	/* If this exit is commented, it will show ALL possible combinations */
	exit(0);
      } else {
	// Recurse!queens(i+1);
      }
    }// if
  }// for
}

int empty(int i) {
  int j;
  j=1;
  while(t[i]!=t[j] && abs(t[i]-t[j])!=(i-j) &&j<8)j++;
  return((i==j)?1:0);
}

void print_solution() {
  int i;
  for(i=1;i<=8;i++)
    printf("\nt[%d] = [%d]",i,t[i]);
}

int main (int argc, char **argv) {
  int ret = 0;

  queens(1);
  print_solution();
  printf ("\n");
  debug("\nOutput = %d", ret);
  return 0;
}

/**
   => ./a.out

   t[1] = [9]
   t[2] = [0]
   t[3] = [0]
   t[4] = [0]
   t[5] = [0]
   t[6] = [0]
   t[7] = [0]
   t[8] = [0]
   [main] L=73 :
   Output = 0
**/
