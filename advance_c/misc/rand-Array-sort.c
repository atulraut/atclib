#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    printf("Hello world!\n");
    int i, j, randNum;
    int arr[5];
    int flag = 0;
    randNum  = rand () % 5;
    arr[0] =  randNum;

    for (j=0; j<5; j++)
    {
        randNum  = rand () % 10;
        for (i=0; i<j; i++)
        {
            if (arr[j] == randNum)
            {
                randNum  = rand () % 5;
            }
            else
            {
                arr[j] =  randNum;
            }
        }
        printf ("\n randNum = %d :: %d\n",i, arr[i]);
    }
    return 0;
}
