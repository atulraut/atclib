/***
    http://haifux.org/lectures/68/mgp00016.html
    Read-Only Memory - Example
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define DEBUG 0

/***
    The following code will cause a SEGV signal in instruction '1'
 */
int  sigv_crash() {
  const char *s = "Hello World";
  printf ("[%s] Enter %d \n",__func__,  __LINE__);

  char *p = (char *) s;
  printf ("[%s] Enter %d \n",__func__,  __LINE__);
  p[0] = 'a'; /* '1' */
  printf ("[%s] End %d \n",__func__,  __LINE__);
  return 0;
}

/***
    The following code won't crash (but is still written with bad style)
 */
int  sigv_crash_fix() {
  const char *t = "Hello World";
  const char *s = strdup(t);

  printf ("[%s] Enter %d \n",__func__,  __LINE__);

  char *p = (char *) s;
  p[0] = 'a'; /* '1' */
  printf ("[%s] End %d \n",__func__,  __LINE__);
  return 0;
}

int check_const() {
  int i = 20;
  const int *a = 10; // int not modify but ptr is

  printf ("[%s] Before Crash L=%d \n",__func__, __LINE__);
  printf ("[%s] a = %d L=%d \n",__func__, *a, __LINE__);
  //*a = 20; // will throw error → main.c:6:6: error: assignment of read-only location ‘*a’
  a = &i;
  printf ("[%s] a = %d L=%d \n",__func__, *a, __LINE__);
  return 0;
}

int main () {
#ifdef DEBUG
  //  printf ("[%s] ret = %d L=%d \n",__func__, sigv_crash(), __LINE__);
#endif
  printf ("[%s] ret = %d L=%d \n",__func__, sigv_crash_fix(), __LINE__);

  printf ("[%s] ret = %d L=%d \n",__func__, check_const(), __LINE__);

  return 0;
}
