#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct result {
  int output[10];
};

struct result findAliveSoldiers(int input1, int input2, int input3[]) {
  struct result res = {.output = {0} };
  int i, out=0;
  int j=input2-1;
  int flag;

  for(i=input1; i>0; --i) {
    printf ("i=%d s=%d \n", i, input3[j]);
    /* We found the element to get rid off */
    if(i == input3[j]) {
      printf ("Soldger May killed i=%d, left=%d right=%d \n", i, 2*i, ((2*i)+i));
      /* Check for left Child */
      if(2*i <= input1 /*&& (2*i) >input1*/) {
	printf ("Left Child to Ignore = %d i=%d\n", input3[2*i], i);
	res.output[out++] = i;
      } else if (((2*i)+1) <= input1  /*&& ((2*i)+1) >input1*/) { /* Check for right Child */
	printf ("Right Child to Ignore = %d i=%d\n", input3[(2*i)+1], i);
	res.output[out++] = input3[(2*i)+1];
      } else { /* No Child */
	printf ("Getting Killed = %d i=%d\n", input1, i);
	res.output[out++] = i;
      }
      --j;
    } else {
      printf ("Not to Kill = %d \n", i);
    }
  }

  return res;
}

struct result findAliveSoldiers_debug(int input1, int input2, int input3[]) {
  struct result res = {.output = {0} };
  int i, out=0;
  int j=input2;
  int flag;

  for(i=input1; i>0; --i) {
    /* We found the element to get rid off */
    if(i == input3[j]) {
      printf ("Soldger to be killed i=%d, left=%d right=%d \n", i, 2*i, ((2*i)+i));
      /* Check for left Child */
      if(2*i <= input1 && (2*i) >input1) {
	printf ("Left Child to Ignore = %d i=%d\n", input3[2*i], i);
	res.output[out++] = i;
      } else if (((2*i)+1) <= input1  && ((2*i)+1) >input1) { /* Check for right Child */
	printf ("Right Child to Ignore = %d i=%d\n", input3[(2*i)+1], i);
	res.output[out++] = input3[(2*i)+1];
      } else { /* No Child */
	printf ("Element to Ignore = %d i=%d\n", input1, i);
	res.output[out++] = i;
      }
      --j;
    } else {
      printf ("Not to Kill = %d \n", i);
    }
  }

  return res;
}

int main() {
  /*Code To Test the logic
    Creating an example tree
     1
    / \
   2   3
  / \  / \
 4   5 6  7
  */

  int i;
  int input1 = 7;
  int input2 = 2;
  int input3[] = {2,7};
  /*
  int input1 = 7;
  int input2 = 1; // if all dead return 0
  int input3[] = {1};
  */
  struct result res =  findAliveSoldiers(input1, input2, input3);
  for(i=0; i<=input2; i++) {
    printf ("Result Output = %d \n", res.output[i]);
  }
}
