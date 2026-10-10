/***
    https://leetcode.com/problems/string-compression/description/

    443. String Compression

    Given an array of characters chars, compress it using the
    following algorithm:

    Begin with an empty string s. For each group of consecutive repeating
    characters in chars:

    If the group's length is 1, append the character to s.
    Otherwise, append the character followed by the group's length.
    The compressed string s should not be returned separately, but instead,
    be stored in the input character array chars. Note that group lengths
    that are 10 or longer will be split into multiple characters in chars.

    After you are done modifying the input array, return the new length of the array.
    You must write an algorithm that uses only constant extra space.
    Note: The characters in the array beyond the returned length do not matter and should be ignored.

    Input: chars = ["a","a","b","b","c","c","c"]
    Output: 6
    Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
    After modifying the input array in-place, the first 6 characters of chars
    should be ["a","2","b","2","c","3"].

    Input: chars = ["a"]
    Output: 1
    Explanation: The only group is "a", which remains uncompressed since it is a single character.
    After modifying the input array in-place, the first character of chars should be ["a"].

    Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
    Output: 4
    Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
    After modifying the input array in-place, the first 4 characters of chars should be ["a","b","1","2"].

    Constraints:
    1 <= chars.length <= 2000
    chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Oct 10 08:03:04 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

/**
   Key interview takeaway: This is a read/write two-pointer pattern.
   The read pointer identifies consecutive groups, while the write
   pointer builds the compressed output in the same array.
   A useful follow-up question: Why is it safe to overwrite
   the input array without losing unread characters?
   Because every compressed group uses no more space than its original group,
   write never moves ahead of read. Therefore, we never overwrite
   characters that still need to be processed.
**/
int compress(char* chars, int charsSize) {
  int read = 0;
  int write = 0;

  while (read < charsSize) {
    char current = chars[read];
    int count = 0;

    // Count consecutive occurrences
    while (read < charsSize && chars[read] == current) {
      read++;
      count++;
    }

    // Write the character
    chars[write++] = current;

    // Write count only if greater than 1
    if (count > 1) {
      int start = write;

      // Extract digits in reverse order
      while (count > 0) {
	chars[write++] = '0' + (count % 10);
	count /= 10;
      }

      // Reverse digits to correct order
      int left = start;
      int right = write - 1;

      while (left < right) {
	char temp = chars[left];
	chars[left] = chars[right];
	chars[right] = temp;
	left++;
	right--;
      }
    }
  }

  return write;
}

/**
   Alternative — Using sprintf
   For interviews, the first solution demonstrates manual digit handling.
   However, sprintf can simplify the implementation.
**/
int compress_pf(char* chars, int charsSize) {
  int read = 0, write = 0;

  while (read < charsSize) {
    char current = chars[read];
    int count = 0;

    while (read < charsSize && chars[read] == current) {
      read++;
      count++;
    }

    chars[write++] = current;

    if (count > 1) {
      char buf[16];
      int len = sprintf(buf, "%d", count);

      for (int i = 0; i < len; i++)
	chars[write++] = buf[i];
    }
  }

  return write;
}
void test() {
  int ret = 0;
  char arr1[] = {'a','a','b','b','c','c','c'};
  char arr2[] = {'a','a','b','b','c','c','c'};
  ret = compress(arr1, 7);
  debug("Output = %d->[%s]", ret, arr1);
  ret = compress_pf(arr2, 7);
  debug("Output = %d->[%s]", ret, arr2);

}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Time	O(n)	Each character is read once; count digits are written once
   Extra space	O(1)	Only pointers, counters, and temporary variables
   In-place	Yes	Modifies the original chars array
**/
