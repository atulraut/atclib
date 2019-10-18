/*
  copy paste from :o https://stackoverflow.com/questions/7202069/how-can-i-know-the-allocated-memory-size-of-pointer-variable-in-c
*/
#include <stdlib.h>
#include <stdio.h>

void * my_malloc(size_t s) {
  printf ("sizeof(size_t) = %ld s = %ld \n", (sizeof(size_t)), (sizeof(size_t) + s));

  size_t* ret = malloc(sizeof(size_t) + s);

  printf ("[my_malloc] sz ret = %p s = %ld \n", ret, s);

  *ret = s;
  printf ("[my_malloc] sz     ret    = %p *ret= %ld \n", ret, *ret);
  printf ("[my_malloc] sz    &ret    = %p \n", &ret);
  printf ("[my_malloc] sz    &ret[0] = %p \n", &ret[0]);
  printf ("[my_malloc] sz    &ret[1] = %p \n", &ret[1]);
  printf ("[my_malloc] sz    &ret[2] = %p \n", &ret[2]);

 // return ret;
  return &ret[1];
}

void my_free(void * ptr) {
  free( (size_t*)ptr - 1);
}

size_t allocated_size(void * ptr) {

  printf ("[allocated_size] sz PTR-ADR= %p \n", (ptr));
  printf ("[allocated_size] sz szPTR= %zu \n", ((size_t*)ptr)[-1]);

  return ((size_t*)ptr)[-1];
}

int main(int argc, const char ** argv) {
  int* array = NULL;

  array = my_malloc(sizeof(int) * 3); /* int sz = 4 bytes here*/

  printf ("--> [main] Address = %p \n", array);
  printf ("[main] og = %ld \n", allocated_size(array));

  my_free(array);

  return 0;
}
