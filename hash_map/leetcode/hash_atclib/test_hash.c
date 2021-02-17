/*
* Aim : HashMap using C
* Date : Thursday, August 20 2020
* San Diego, CA
* By : Atul R. Raut
* valgrind -v --leak-check=full --show-reachable=yes ./main
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_lib.h"

#define SIZE 1024

struct table *t;

static int get_input() {
  int res = 1;
  char cmd[20] = {0};

  printf ("Enter input! \n");

  while(fgets (cmd, 20, stdin) && cmd[0] != '\n') {
    res = atoi(cmd);
  }
  printf ("atoi=%d, cmd=%s \n", res, cmd);
  return res;
}

void m_TestFunc(void *ptr_dummy) {
  int i;
  int arr[] = {11,12,13,14,15,11, 27, 13, 11};
  int sz = sizeof(arr) / sizeof(arr[0]);

  /* Hold Big Number for Hashing if big input given else array size is Okay */
  t = m_createTable(sz);
  printf ("[%s] --> sz=%d \n", __func__, sz);

  for (i=0; i<sz; i++) {
    m_insert(t, arr[i]);
  }
  /* Lets validate the hashing */
  printf ("[%s] --> Search Eelement \n", __func__);
  for (i=0; i<sz; i++) {
    printf ("[%s] --> Element Found = %d \n", __func__, m_lookup(t, arr[i]));
  }
}

void m_Display(void *ptr){
  int result;
  int data;

  data = get_input();
  printf ("%s Search for Data = %d \n", __func__,  data);
  printf ("\n----------:: Output ::-----------\n");
  printf ("%s Search for Data = %d \n",__func__,  data);
    result = m_lookup(t, data);
    if (result) {
      printf("Found: %d\n", result);
    }
    else {
      printf("Couldn't find %d Exiting! \n", data);
    }
    printf ("\n----------:: End ::-----------\n");
}

void quit(void *_ptr) {
  printf ("Good Bye! \n");
  exit(0);
}
