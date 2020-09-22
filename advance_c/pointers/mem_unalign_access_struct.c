/***
    http://c-faq.com/strangeprob/ptralign.html
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mystruct {
  char c;
  long int i32;
  int i16;
} s;

void foo1 () {
  int count;
  FILE *fp;
  char buf[7], *p; // Buffer to store data

  fp = fopen("file.txt", "r");
  //count = fread(buf, sizeof(char), 30, fp);
  count = fread(buf, 7, 1, fp);
  fclose(fp);
  // Printing data to check validity
  printf("Data read from file: %s \n", buf);
  printf("Elements read: %d \n", count);
  printf ("[%s] Enter 1 L=%d \n", __FILE__, __LINE__);

  /* Fix Me */
  p = buf;
  s.c = *p++;
  s.i32 = (long)*p++ << 24;
  s.i32 |= (long)*p++ << 16;
  s.i32 |= (unsigned)(*p++ << 8);
  s.i32 |= *p++;

  s.i16 = *p++ << 8;
  s.i16 |= *p++;

  printf ("[%s] c=%c i32=%ld i16=%d L=%d \n", __FILE__, s.c, s.i32, s.i16, __LINE__);
}

void foo2() {
int count;
  FILE *fp;
  char buf[7], *p; // Buffer to store data

  fp = fopen("file.txt", "r");
  //count = fread(buf, sizeof(char), 30, fp);
  count = fread(buf, 7, 1, fp);
  fclose(fp);
  // Printing data to check validity
  printf("Data read from file: %s \n", buf);
  printf("Elements read: %d \n", count);
  printf ("[%s] Enter 1 L=%d \n", __FILE__, __LINE__);

  /* Fixed! */
  p = buf;
  s.c = *p++;
  s.i32 = *(long int *)p;
  p += 4;
  s.i16 = *(int *)p;
  printf ("[%s] c=%c i32=%ld i16=%d L=%d \n", __FILE__, s.c, s.i32, s.i16, __LINE__);
}

int main () {
  foo1();
  foo2();
}
