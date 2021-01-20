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

/***
    Algorithm : Iterative
    E0 : [Ensure m>= n] - if m<n, exchange m <--> n.
    E1 : [Find Reminder]- Divide m by n and let r be the remdiner - 0 <0 r <- n
    E2 : [Is it zero?]  - If r=0, the algorithm terminates; n is the answer
    E3 : [Reduce] Set m<--n, n<--r, & goback to step E1 |
*/

/* Witnout Recursion: Function to return gcd of a and b */
int gcd(int m, int n)  {
  int reminder = 0;

  /* E0 */
  if (m < n) {
    reminder = m;
    m = n;
    n = reminder;
  }

  while(n) {
    printf ("[%s] m = %d n = %d \n", __func__, m, n);
    /* E1 */
    reminder = m % n;
    printf ("[%s] r = %d \n",  __func__, reminder);
    /* E2 */
    if (reminder == 0)
      break;
    /* E3 */
    m = n;
    n = reminder;
    printf ("[%s] m = %d n = %d \n",  __func__, m, n);
  };
  return n;
}

// Iterative algorithm
int gcd_one(int m, int n) {
  int reminder;
  while(n) {
    reminder = m % n;
    printf ("-->%d\n", reminder);
    m = n;
    n = reminder;
  }
  return(m);
}

/* Recursive algorithm */
int gcd_recurse(int m, int n) {
  int temp;
  temp = m % n;
  if (temp == 0) {
    return(n);
  } else {
    return(gcd_recurse(n, temp));
  }
}

// Function to return gcd of m and n
int gcd_rec(int m, int n)  {
    if (m == 0)
        return n;
    return gcd(n % m, m);
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
  int m = 544, n=119;

  printf ("[%s]--> %d\n",  __func__, gcd (m, n));

  for (n = 1; n <= 10; n++)
    printf ("phi = %d \n",phi(n));
  return 0;
}

/***
    => ./a.out
    phi = 1
    phi = 1
    phi = 2
    phi = 2
    phi = 4
    phi = 2
    phi = 6
    phi = 4
    phi = 6
    phi = 4
*/
