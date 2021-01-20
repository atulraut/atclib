/***
    Write a C program to reverse the words in a sentence in place.
    That is, given a sentence like this
    I am a good boy
    The in place reverse would be
    boy good a am I
    Method1
    First reverse the whole string and then individually reverse the words
    I am a good boy
    <------------->
    yob doog a
    <-> <--> <->
    ma
    I
    <-> <->
    boy good a am I
    Here is some C code to do the same ....
*/
/***
  Algorithm..
  1. Reverse whole sentence first.
  2. Reverse each word individually.
  All the reversing happens in-place.
*/

#include <stdio.h>

void rev(char *l,char *r) {
  char t;
  printf ("[%s] l=%c r=%c L=%d\n",__func__, *l, *r, __LINE__);
  while(l<r) {
    t  = *l;
    *l++ = *r;
    *r-- = t;
  }
}

void reverse_word () {
  char buf[] = "I am a good boy";
  char *end, *x, *y;

  // Reverse the whole sentence first..
  for(end=buf; *end; end++);
    rev(buf, end-1);

  printf("[%s] %s L=%d \n",__func__, buf, __LINE__);

  // Now swap each word within sentence...
  x = buf-1;
  y = buf;
  while(x++ < end) {
      if(*x == '\0' || *x == ' ') {
	  rev(y, x-1);
	  y = x+1;
      }
  }

  // Now print the final string....
  printf("[%s] %s L=%d \n",__func__, buf, __LINE__);
}


int main(int argc, char *argv[]) {
  reverse_word();
  return(0);
}
