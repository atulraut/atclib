/***
    Can we modify the Value of 'Const' variable ?
    Answer : Yes, We can modify value of a 'Const' Variable by using Pointers.
    Note : We can not Modify value of Constant Global Variable because a Const
    Global Variable is Stored into 'READ ONLY MEMORY'. We will get 'Segmentation Fault'
    Ref: https://www.geeksforgeeks.org/how-to-modify-a-const-variable-in-c/
    Date : 18 March 2021.
    San Diego, CA.
 */
#include <limits.h>
#include <stdio.h>

const int var = 15;

void foo () {
  const int a = 10;
  //a = 15;  // modify_const.c:14:5: error: assignment of read-only variable ‘a’
  int *ptr = &a;
  *ptr = 15;
  printf ("[%s] Enter var = %d L=%d \n", __func__, a, __LINE__);

  *ptr = &var;
  *ptr = 25;
  printf ("[%s] Enter var = %d L=%d \n", __func__, a, __LINE__);
}

int main() {
  foo();
  return 0;
}
