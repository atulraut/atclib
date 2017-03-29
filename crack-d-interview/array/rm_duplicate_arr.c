/*
* remove duplicates elements from array
*/
#include<stdio.h>

int del_dup_array (int *arr, int size);
void rev (int x);
//int ar[] = {1,2,3,4,2,2, 6,7,8,9,11,12,24,45,45,46,33,36,32,7,87,79,65,43,21};
int ar[] = {1,2,2,3,2,21};
int del_dup_array (int arr[], int size) {
  int i, j, k;
  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size;) {
      if (arr[j] == arr[i]) {
	    for (k=j; k<size; k++) {
	         if ((size-1) == k)
	             arr[k+1] = 0;
		 //	    	 printf ("i=%d, j=%d, k=%d, k=[%d], k+1=[%d] size = %d\n",i,j,k,  arr[k], arr[k + 1], size);
	         arr[k] = arr[k + 1];
	    }
	    size--;
      } else
        j++;
    }
  }
  return size;
}

int main() {
  int i, j, k, size=5;

  size = sizeof(ar) / sizeof(ar[0]);
  printf("Array with Unique list  : %d \n", size);
  size = del_dup_array (ar, size);
  for (i = 0; i < size; i++) {
    printf("->[%d] ", ar[i]);
  }
  printf ("\n");
  rev (2);
  return (0);
}

void rev (int x) {
  int i;
  unsigned int y;
  for (i=1; i<=10; i++) {
    y = (i << 3) - (i << 0);
    printf ("\n Mul by 07 = ->[%d] ", y);
  }
  for (i=1; i<=10; i++) {
    y = (i << 3) + (i << 1);
    printf ("\n Mul by 10 = ->[%d] ", y);
  }
  x=1;
  printf ("\nx[0] = %d ", (x << 0));
  printf ("\nx[1] = %d ", (x << 1));
  printf ("\nx[2] = %d ", (x << 2));
  printf ("\nx[3] = %d ", (x << 3));
  printf ("\nx[4] = %d \n",(x << 4));
}
