/*
* Aim : 10. Print the Floyed's Triangle.
	1
	2 3
	4 5 6
	7 8 9 10
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, a;
    int b=1;
    printf("Welcome....!\n");
    for (i=1; i<=4; i++)
    {
        printf ("\n");
        for (j=1; j<=i; j++)
        {
            printf ("% 2d", b);
                   b++;
        }
    }
    return 0;
}
