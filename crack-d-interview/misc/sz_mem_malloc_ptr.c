/*
  Ref:
   https://stackoverflow.com/questions/7202069/how-can-i-know-the-allocated-memory-size-of-pointer-variable-in-c
*/
#include <stdlib.h>
#include <stdio.h>

void * my_malloc(size_t s) {
  printf ("[%s] sizeof(size_t) = %ld s = %ld \n",__func__, (sizeof(size_t)), (sizeof(size_t) + s));

  size_t* ret = malloc(sizeof(size_t) + s);

  printf ("[%s] sz ret = %p s = %ld \n",__func__, ret, s);

  *ret = s;
  printf ("[%s] sz    ret     = %p *ret= %ld \n",__func__, ret, *ret);
  printf ("[%s] sz    &ret    = %p \n", __func__, &ret);
  printf ("[%s] sz    &ret[0] = %p \n",__func__, &ret[0]);
  printf ("[%s] sz    &ret[1] = %p \n",__func__, &ret[1]);
  printf ("[%s] sz    &ret[2] = %p \n",__func__, &ret[2]);

 // return ret;
  return &ret[1];
}

void my_free(void * ptr) {
  free( (size_t*)ptr - 1);
}

size_t allocated_size(void * ptr) {

  printf ("[%s] sz PTR-ADR= %p \n",__func__, (ptr));
  printf ("[%s] sz szPTR= %zu \n",__func__, ((size_t*)ptr)[-1]);

  return ((size_t*)ptr)[-1];
}

int main(int argc, const char ** argv) {
  int* array = NULL;

  array = my_malloc(sizeof(int) * 3); /* int sz = 4 bytes here*/

  printf ("[%s] Address = %p \n",__func__, array);
  printf ("[%s] og = %ld \n",__func__, allocated_size(array));

  my_free(array);

  return 0;
}

/***
    => ./a.out
    [my_malloc] sizeof(size_t) = 8 s = 20
    [my_malloc] sz ret = 0x85b420 s = 12
    [my_malloc] sz    ret     = 0x85b420 *ret= 12
    [my_malloc] sz    &ret    = 0x7fffd7382150
    [my_malloc] sz    &ret[0] = 0x85b420
    [my_malloc] sz    &ret[1] = 0x85b428
    [my_malloc] sz    &ret[2] = 0x85b430
    [main] Address = 0x85b428
    [allocated_size] sz PTR-ADR= 0x85b428
    [allocated_size] sz szPTR= 12
    [main] og = 12
*/
