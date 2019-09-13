/*
 * Aim  : Function Pointer Explain
 * Date : 9-12-19
 **/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct calc_func {
  int (*compute)();
  char key;
  char *name;
};

int add() {
  char cmd[20];
  int x, res = 0;

  printf ("Enter numbers to Add! \n");
  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res += atoi(cmd);
  }
  printf ("Resule is = %d \n", res);
}

int minus() {
  char cmd[20];
  int x, res = 0;

  printf ("Enter numbers to Subtract! \n");
  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res -= atoi(cmd);
  }
  printf ("Resule is = %d \n", res);
}

int multiply() {
  char cmd[20] = {0};
  int x, res = 1;

  printf ("Enter numbers to Multiply! \n");
  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res *= atoi(cmd);
    printf ("res = %d atoi=%d, cmd=%s \n",res, atoi(cmd), cmd);
  }
  printf ("Resule is = %d \n", res);
}

int quit() {
  printf ("Good Bye! \n");
  exit(0);
}

struct calc_func function_stat[] = {
  {
    .compute = add,
    .key = '+',
    .name = "Add",
  },
  {
    .compute = minus,
    .key = '-',
    .name = "Subtract",
  },
  {
    .compute = multiply,
    .key = '*',
    .name = "Multiply",
  },
  {
    .compute = quit,
    .key = 'q',
    .name = "Quit",
  },
};

#define NB_FUNCS (sizeof(function_stat)/(sizeof(struct calc_func)))

void printf_all_functions() {
  int i;
  for(i=0; i<NB_FUNCS; i++) {
    printf ("--> Press key %c for %s \n", function_stat[i].key, function_stat[i].name);
  }
}

int main() {
  int i = 0;
  char cmd[20];
  printf ("sz-> %ld\n", NB_FUNCS);
  printf ("-> %ld %ld\n", (sizeof(function_stat)), (sizeof(struct calc_func)) );

  printf ("Welcome to simple Calculator 1.0 \n");
  printf ("===================================");
  printf_all_functions();
  printf ("===================================\n");

  while(1) {
    printf("Enter a command \n");
    fgets(cmd, 20, stdin);

    for(i=0; i<NB_FUNCS; i++) {
      if(function_stat[i].key == cmd[0]) {
	printf ("Calling command: %s \n", function_stat[i].name);
	function_stat[i].compute();
	break;
      }
    }
  }
}
