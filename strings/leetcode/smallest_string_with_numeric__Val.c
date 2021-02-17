/***
    1663. Smallest String With A Given Numeric Value using C
    The numeric value of a lowercase character is defined as its position (1-indexed)
    in the alphabet, so the numeric value of a is 1, the numeric value of b is 2,
    the numeric value of c is 3, and so on.

    The numeric value of a string consisting of lowercase characters is defined
    as the sum of its characters' numeric values. For example, the numeric value
    of the string "abe" is equal to 1 + 2 + 5 = 8.

    You are given two integers n and k. Return the lexicographically smallest string
    with length equal to n and numeric value equal to k.

    Note that a string x is lexicographically smaller than string y if x comes before
    y in dictionary order, that is, either x is a prefix of y, or if i is the first
    position such that x[i] != y[i], then x[i] comes before y[i] in alphabetic order.

    Example 1:
    Input: n = 3, k = 27
    Output: "aay"
    Explanation: The numeric value of the string is 1 + 1 + 25 = 27, and it is the
    smallest string with such a value and length equal to 3.

    Example 2:
    Input: n = 5, k = 73
    Output: "aaszz"

    Constraints:
    1 <= n <= 105
    n <= k <= 26 * n

    Algorithm :
    Build a string or character array result to store the character chosen for
    each position.
    Start iterating from last position n-1 and allocate maximum possible
    numeric value to each position based on remaining k.
    We know that the largest character at any position could be z with numeric
    value 262626. Also, we must leave some value from k, that is, 1 numeric
    value for each remaining position (k - position). Thus the maximum numeric value
    for the current position given by add can be calculated as, minimum of k - position and 26.
    Subtract the value calculated for the current position add from k.
    The process would continue until all the positions are filled, with reducing K at each iternation.

    Date : 1-29-21
    San Diego, CA
    1] https://stackoverflow.com/questions/12380758/error-function-returns-address-of-local-variable
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))

/***
    LeetCode Accepted: 20ms
 */
char * getSmallestString(int n, int k){
  char *result_ptr = (char *)malloc(n+1);
  int position;
  int add;

  for (position = n - 1; position >= 0; position--) {
    add = min(k - position, 26); /*Logic is to reduce k, so k=30, it can be 25+5 or 26 + 4, we want former one, */
    result_ptr[position] = (char)(add + 'a' - 1);  /* Try to make Small Char by adding + a*/
    //printf ("[%s] add = %d , 'a' = %d char = %c \n", __func__, add, 'a', (char)(add + 'a' - 1));
    k -= add;
  }
  result_ptr[n] = '\0';
  return result_ptr;
}

char* getSmallestString2(int n, int k) {
  char result[n+1];
  char *result_ptr = result;
  int position;
  int add;

  for (position = n - 1; position >= 0; position--) {
    add = min(k - position, 26); /*Logic is to reduce k, so k=30, it can be 25+5 or 26 + 4, we want former one, */
    result_ptr[position] = (char)(add + 'a' - 1);  /* Try to make Small Char by adding + a*/
    printf ("[%s] add = %d , 'a' = %d char = %c \n", __func__, add, 'a', (char)(add + 'a' - 1));
    k -= add;
  }
  result[n] = '\0';
  printf ("result = %s \n", result);
  return result_ptr;
}

int main () {
  int n = 3;
  int k = 27;
  char *ret = getSmallestString(n, k);
  printf ("[%s] result = %s \n", __func__, ret);
  free(ret);
}

/***

    Complexity Analysis :
    Time Complexity: O(n)\mathcal{O}(n)O(n), as we iterate over nnn positions to build the resultant string.
    Space Complexity: O(1)\mathcal{O}(1)O(1), as we use constant extra space to store add and position variables.
*/

/***
    => ./main
    [getSmallestString] add = 25 , 'a' = 97 char = y
    [getSmallestString] add = 1 , 'a' = 97 char = a
    [getSmallestString] add = 1 , 'a' = 97 char = a
    result = aay
    [main] result = aay

To Fix below Error Check link 1 above in comment, no need to allocate memory.
==>  gcc smallest_string_with_numeric__Val.c -o main -Wall -Werror -g -fsanitize=address

=> ./main
result = 0x60200000eff0
=================================================================
==19945==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60200000eff4 at pc 0x7f168c09f1e9 bp 0x7ffefb7f91b0 sp 0x7ffefb7f8928
READ of size 5 at 0x60200000eff4 thread T0
    #0 0x7f168c09f1e8  (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x601e8)
    #1 0x7f168c09f7f7 in __interceptor_vprintf (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x607f7)
    #2 0x7f168c09f907 in __interceptor_printf (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x60907)
    #3 0x4009c1 in getSmallestString /home/atul/dev/c/to_push/atclib/leetCode/string/smallest_string_with_numeric__Val.c:30
    #4 0x400a01 in main /home/atul/dev/c/to_push/atclib/leetCode/string/smallest_string_with_numeric__Val.c:40
    #5 0x7f168bc9583f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)
    #6 0x4007f8 in _start (/home/atul/dev/c/to_push/atclib/leetCode/string/main+0x4007f8)

0x60200000eff4 is located 0 bytes to the right of 4-byte region [0x60200000eff0,0x60200000eff4)
allocated by thread T0 here:
    #0 0x7f168c0d7602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x4008ec in getSmallestString /home/atul/dev/c/to_push/atclib/leetCode/string/smallest_string_with_numeric__Val.c:18
    #2 0x400a01 in main /home/atul/dev/c/to_push/atclib/leetCode/string/smallest_string_with_numeric__Val.c:40
    #3 0x7f168bc9583f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2083f)

SUMMARY: AddressSanitizer: heap-buffer-overflow ??:0 ??
Shadow bytes around the buggy address:
  0x0c047fff9da0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9db0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9dc0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9dd0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9de0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x0c047fff9df0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa[04]fa
  0x0c047fff9e00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e10: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e20: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e30: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e40: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Heap right redzone:      fb
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack partial redzone:   f4
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
==19945==ABORTING

*/
