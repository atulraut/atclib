/***
    Quick-find solution to connectivity Problem

    #algoinc

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Jul  1 09:36:33 AM PDT 2022
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
#include <time.h>

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

static int _localtime_() {
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  debug ( "Current local time and date: %s", asctime (timeinfo) );

  return 0;
}

void quit() {
  debug ("Exiting Bbye!");
  exit(0);
}

void display() {

}

void test6() {

}

void test5() {

}

void test4() {

}


/***
 * Excercises 2.2
 */
void test3() {
  long int N = 123456789;
  int i, j, k, count = 0;
  debug("Enter - ");
  _localtime_();
  //  for (i=0; i<N; ++i)
    for (j=0; j<N; ++j)
      for (k=0; k<N; ++k)
	++count;
  debug ("--> %d", count);
  _localtime_();
}

/**
    Progam 1.3
    Weighted version fo Quick Union
*/
#define N 10
int id[N];

void test2() {
  int ret = 0;
  int i=0, j=0, p=0, q=0, t=0;
  int sz[N] = {0};

  for (i=0; i<N; i++) {
    id[i] = i;
    sz[i] = 1;
  }

  while (scanf("%d %d \n", &p, &q) == 2) {
    for (i=p; i != id[i]; i=id[i])
      ;
    for (j=q; j != id[j]; j=id[j])
      ;
    if (i == j)
      continue;
    if (sz[i] < sz[j]) {
      id[i] = j;
      sz[j] += sz[i];
    } else {
      id[j] = i;
      sz[i] += sz[j];
    }
    debug ("--> %d %d  \n", p, q);
  }
}

/* Program 1.1 */
void test() {
  int ret = 0;
  int i, p, q, t, id[N];

  for (i=0; i<N; ++i) {
    id[i] = i;
  }

  while (scanf("%d %d \n", &p, &q) == 2) {
    if (id[p] == id[q])
        continue;
    for (t= id[p]; i=0, i<N; ++i) {
      if (id[i] == t)
	id[i] = id[q];
      printf ("%d %d \n", p, q);
    }
  }
  debug("Output = %d", ret);
}

void QuickFindU() {
  //  id[N] = {0, 1, 2, 3, 8, 0, 5, 7 ,3, 8};
}

int connected (int p, int q) {
  return (id[p] == id[q]);
}

void union2 (int p, int q) {
  int pid = id[p];
  int qid = id[q];

  // Change all Entries with id[p] to id[q] (at most 2N+2 array accesses)
  for (int i=0; i<N; ++i)
    if (id[i] == pid)
      id[i] = qid;
}

struct func_compute {
  char key;
  char* name;
  void (*compute) ();
};

struct func_compute comp[] = {
  {
    .key = '1',
    .name= "test-1",
    .compute = test
  },
  {
    .key = '2',
    .name= "test-2",
    .compute = test2
  },
  {
    .key = '3',
    .name= "test-3",
    .compute = test3
  },
  {
    .key = '4',
    .name= "test-4",
    .compute = test4
  },
  {
    .key = '5',
    .name= "test-5",
    .compute = test5
  },
  {
    .key = '6',
    .name= "test-6",
    .compute = test6
  },
  {
    .key = '7',
    .name= "Display",
    .compute = display
  },
  {
    .key = '9',
    .name= "Quit",
    .compute = quit
  }
};

#define NB_FUNCS (sizeof(comp)/sizeof(struct func_compute))

void printf_all_functions() {
  debug ("Enter!\n");
  for(int i=0; i<NB_FUNCS; i++)
    printf ("--> Press key %c for %s \n", comp[i].key, comp[i].name);
}

int main (int argc, char **argv) {
  int i = 0;
  char cmd[20];
  printf ("Avaiable Routines = %ld\n", NB_FUNCS);
  printf ("Welcome to Simple Unix Buffer Cache Using C! \n");
  printf ("===================================");
  printf_all_functions();
  printf ("===================================\n");
  while(1) {
    debug("Enter an Command!");
    fgets(cmd, 20, stdin);

    for (i=0; i<NB_FUNCS; ++i) {
      if (comp[i].key ==  cmd[0]) {
	debug ("Calling Command: %s ", comp[i].name);
	comp[i].compute();
	break;
      }
    }
  }
  debug ("End!");

  return EXIT_SUCCESS;
}

/**

 **/
