/*
  Euler’s Totient function ?(n) for an input n is count of
  numbers in {1, 2, 3, …, n} that are relatively prime to n,
  i.e., the numbers whose GCD (Greatest Common Divisor) with n is 1.
  ?(1) = 1
  gcd(1, 1) is 1
  ?(2) = 1
  gcd(1, 2) is 1, but gcd(2, 2) is 2.
  ?(3) = 2
  gcd(1, 3) is 1 and gcd(2, 3) is 1
*/
#include <stdio.h>
#include <stdlib.h>

// Function to return gcd of a and b
int gcd(int a, int b)  {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

// A simple method to evaluate Euler Totient Function
int phi(unsigned int n)  {
    unsigned int result = 1;
    for (int i = 2; i < n; i++)
        if (gcd(i, n) == 1)
            result++;
    return result;
}

int main()  {
    int n;
    for (n = 1; n <= 10; n++)
      printf ("phi = %d \n",phi(n));
    return 0;
}

