#include <stdio.h>
#include <stdlib.h>

int printIntersection(int arr1[], int arr2[], int m, int n)
{
  int i = 0, j = 0;
	printf ("Intersection \n");
  while (i < m && j < n)
  {
    if (arr1[i] < arr2[j])
      i++;
    else if (arr2[j] < arr1[i])
      j++;
    else /* if arr1[i] == arr2[j] */
    {
      printf(" %d ", arr2[j++]);
      i++;
    }
  }
  printf ("\n");
}

int printUnion(int arr1[], int arr2[], int m, int n)
    {
      int i = 0, j = 0;
	printf ("Print Union \n");
      while (i < m && j < n)
      {
        if (arr1[i] < arr2[j])
          printf("--> %d ", arr1[i++]);
        else if (arr2[j] < arr1[i])
          printf("--> %d ", arr2[j++]);
        else
        {
          printf("--> %d ", arr2[j++]);
          i++;
        }
      }
      printf ("\n");
      /* Print remaining elements of 
         the larger array */
      while(i < m)
       printf("--> %d ", arr1[i++]);
      while(j < n)
       printf("--> %d ", arr2[j++]);
      printf ("\n");  
      return 0;   
}

int main () {
	int arr1[] = {1, 2, 4, 5, 6};
        int arr2[] = {2, 3, 5, 7};
        int m = sizeof(arr1)/arr1[0];
        int n = sizeof(arr2)/arr2[0];
	//        printUnion(arr1, arr2, m, n);
	//	printIntersection(arr1, arr2, m, n);
}
