/*
*   Aim : 9. Print the following structure.
         1 1
       2 1 1 2
     3 2 1 1 2 3
   4 3 2 1 1 2 3 4
* Start Date : 25-06-2009
*
**/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j;
    for (i=1; i<=4; i++)
    {
        printf ("\n");
        for (j=4; j>=i; j--)
        {
            printf ("%2d", j);
        }
    }
    return 0;
}

/*  Below Code for printing :
  1
  1 2
  1 2 3
  1 2 3 4

    for (i=1; i<=4; i++)
    {
        printf ("\n");
        for (j=1; j<=i; j++)
        {
            printf ("%2d", j);
        }
    }
*/
