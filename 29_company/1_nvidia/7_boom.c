/**
 7Boom question - write a program to print numbers sequentially.
 Every number containing the digit 7 should instead be printed as boom

    Tue Oct  6 22:21:45 PDT 2026
**/

#include <stdio.h>
#include <limits.h>

/*
 * Return 1 if n contains the requested digit.
 * Return 0 otherwise.
 *
 * n is assumed to be non-negative.
 */
int contains_digit(int n, int digit) {
    /* Special case: number 0 contains digit 0 */
    if (n == 0)
        return (digit == 0);

    while (n > 0) {
        int current_digit = n % 10;

        if (current_digit == digit)
            return 1;

        n /= 10;
    }

    return 0;
}

/*
 * Print numbers from start to end.
 * If a number contains 'digit', print "Boom".
 */
void print_boom(int start, int end, int digit) {
    if (start < 0 || end < start)
        return;

    int i = start;

    while (1) {

        if (contains_digit(i, digit))
            printf("Boom\n");
        else
            printf("%d\n", i);

        /*
         * Check before incrementing.
         *
         * This is important when end == INT_MAX.
         * Otherwise INT_MAX + 1 causes signed integer overflow.
         */
        if (i == end)
            break;

        i++;
    }
}

int main(void) {
    int digit;
    int end;

    printf("Enter Boom digit (0-9): ");

    if (scanf("%d", &digit) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }

    if (digit < 0 || digit > 9) {
        printf("Error: Please enter a digit between 0 and 9\n");
        return 1;
    }

    printf("Enter ending number: ");

    if (scanf("%d", &end) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }

    if (end < 1) {
        printf("Error: Ending number must be >= 1\n");
        return 1;
    }

    printf("\nPrinting from 1 to %d\n", end);
    printf("Numbers containing %d will be replaced with Boom\n\n",
           digit);

    print_boom(1, end, digit);

    return 0;
}

/**
  $ ./a.out
  Enter Boom digit (0-9): 7
  Enter ending number: 9

  Printing from 1 to 9
  Numbers containing 7 will be replaced with Boom

	1
	2
	3
	4
	5
	6
	Boom
	8
	9
**/
