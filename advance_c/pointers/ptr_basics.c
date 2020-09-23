/***
 *  objdump -dS --prefix-strip=12   --disassemble a.out  > my.dump
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void foo3() {

}

// sizeof is compile time perator
void foo2() {
  int a = 3;
  printf ("[%s] value of a= %d \n",__func__, a);
  printf ("[%s] sizeof = %ld \n",__func__, sizeof(++a));
  printf ("[%s] value of a= %d \n",__func__, a);
}


/***
 * It print scal factor :
 * If this is what you are asking, %p and %Fp print out a pointer,
 * specifically the address to which the pointer refers, and since it is
 * printing out a part of your computer's architecture, it does so in Hexadecimal.
 * In C, you can cast between a pointer and an int, since a pointer is just a 32-bit
 * or 64-bit number (depending on machine architecture) referring to the
 * aforementioned chunk of memory.
 * https://stackoverflow.com/questions/12633067/p-format-specifier-in-c
*/
void foo1() {
  void* p0 = NULL;   // 1
  char* p1 = NULL;   // 1
  short* p2 = NULL;  // 2
  float* p3 = NULL;  // 4
  double* p4 = NULL; // 8
  printf("[%s] p0=%p, p1=%p, p2=%p, p3=%p p4=%p \n",__func__, ++p0, ++p1, ++p2, ++p3, ++p4);
}

int main () {
  foo1();
  foo2();
  foo3();
  return 0;
}
