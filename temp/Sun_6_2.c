/*
*   Aim : 2) Find maximum and minimum of 10 integers.
*   Print the result along with the numbers entered.
**/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, k;
    printf("Hello world!\n");
    int arr[10] = {1, 4, 5, 6, 8 ,2 ,3 ,7 ,9};
    int *brr;
    int temp;
    brr = &arr;
    for (i=1; i<10; i++)
    {
        for (k=0; k<9; k++)
        {
            if (arr[i] < brr[k])
                {
                    temp = arr[i];
                    arr[i] = brr[k];
                    brr[k] = temp;
                }
        }
    }
    printf ("\nBuble Sort, ascending order : \n");
    for (k=1; k<10; k++)
        {
            printf ("\n%d] = %d",k ,arr[k]);

        }
        printf ("\nMax is = %d", arr[8]);
        printf ("\nMin is = %d", arr[0]);
    return 0;
}
