#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, a;
    int b = 1;
    printf("Hello world!\n");
    for (i=1; i<=5; i++)
    {
        printf ("\n");
        for (j=1; j<=i; j++)
        {
            printf ("%d", b);
            if (j == b)
            {
                getch ();
                break;
            }
          //  b++;
        }
        b++;
    }
    return 0;
}
