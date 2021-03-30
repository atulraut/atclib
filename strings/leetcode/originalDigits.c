/***
    423. Reconstruct Original Digits from English
    https://leetcode.com/problems/reconstruct-original-digits-from-english/
    Given a non-empty string containing an out-of-order English representation
    of digits 0-9, output the digits in ascending order.

    Note:
    Input contains only lowercase English letters.
    Input is guaranteed to be valid and can be transformed to its original digits.
    That means invalid inputs such as "abc" or "zerone" are not permitted.
    Input length is less than 50,000.

    Example 1:
    Input: "owoztneoer"
    Output: "012"

    Date : 29 March 2021
    San Diego, CA
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

#define SIZE 12000

void function(int *map, int num, char* s){
  int len = strlen(s);
  for(int i=0; i<len; i++){
    map[s[i]-'a'] -= num;
    debug ("s[%d] = %c, num=%d  [s[i]-'a']=%d map=%d", i, s[i], (s[i]-'a'), num, map[s[i]-'a']);
  }
}

char* originalDigits(char* s) {
  int *map = (int*)calloc(26,sizeof(int));
  int len = strlen(s);

  for(int i=0; i<len; i++)
    map[s[i]-'a']++;

  char *array[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
  };

  char *ret = (char*)malloc(SIZE*sizeof(char));
  int count = 0;
  int *nums = (int*)calloc(10,sizeof(int)); // allocate 10 bytes memory

  /* building hashmap digit -> its frequency */
  nums[0] = map['z'-'a'];              // 0 : letter "z" is present only in "Zero"
  function(map, nums[0], array[0]);
  nums[2]=map['w'-'a'];                // 2 : letter "w" is present only in "tWo"
  function(map, nums[2], array[2]);
  nums[4]=map['u'-'a'];                // 4 : letter "u" is present only in "foUr"
  function(map, nums[4], array[4]);
  nums[6]=map['x'-'a'];                // 6 : letter "x" is present only in "siX"
  function(map, nums[6], array[6]);
  nums[8]=map['g'-'a'];                // 8 : letter "g" is present only in "eiGht"
  function(map, nums[8], array[8]);
  nums[1]=map['o'-'a'];                // 1 : One
  function(map, nums[1], array[1]);
  nums[3]=map['t'-'a'];                // 3 : Three
  function(map, nums[3], array[3]);
  nums[5]=map['f'-'a'];                // 5 : Five
  function(map, nums[5], array[5]);
  nums[7]=map['s'-'a'];                // 7 : Seven
  function(map, nums[7], array[7]);
  nums[9]=map['i'-'a'];                // 9 : nIne
  function(map, nums[9], array[9]);

  for(int i = 0; i<10; i++) {
    for(int j = 0; j<nums[i]; j++) {
      ret[count++]= i + '0';
    }
  }

  ret[count++]='\0';
  return ret;
}

int main () {
  char str[] = "owoztneoer";
  char *op  = originalDigits(str);

  debug ("--> %s ", op);            ;

  return 0;
}

/**
   => ./a.out
   [main] L=96 :--> 012
**/

/**
   Complexity Analysis
   Time complexity : O(N) where N is a number of
   characters in the input string. O(N)\mathcal{O}(N)O(N) time is needed
   to compute hashmap count "letter -> its frequency in the input string".
   Then we deal with a data structure out which contains 10 elements only
   and all operations are done in a constant time.

   Space complexity : O(1). count contains constant
   number of elements since input string contains only lowercase English
   letters, and out contains not more than 10 elements.
**/

/**
   => ./a.out
   [function] L=40 :s[0] = z, num=25  [s[i]-'a']=1 map=0
   [function] L=40 :s[1] = e, num=4   [s[i]-'a']=1 map=1
   [function] L=40 :s[2] = r, num=17  [s[i]-'a']=1 map=0
   [function] L=40 :s[3] = o, num=14  [s[i]-'a']=1 map=2
   [function] L=40 :s[0] = t, num=19  [s[i]-'a']=1 map=0
   [function] L=40 :s[1] = w, num=22  [s[i]-'a']=1 map=0
   [function] L=40 :s[2] = o, num=14  [s[i]-'a']=1 map=1
   [function] L=40 :s[0] = f, num=5   [s[i]-'a']=0 map=0
   [function] L=40 :s[1] = o, num=14  [s[i]-'a']=0 map=1
   [function] L=40 :s[2] = u, num=20  [s[i]-'a']=0 map=0
   [function] L=40 :s[3] = r, num=17  [s[i]-'a']=0 map=0
   [function] L=40 :s[0] = s, num=18  [s[i]-'a']=0 map=0
   [function] L=40 :s[1] = i, num=8   [s[i]-'a']=0 map=0
   [function] L=40 :s[2] = x, num=23  [s[i]-'a']=0 map=0
   [function] L=40 :s[0] = e, num=4   [s[i]-'a']=0 map=1
   [function] L=40 :s[1] = i, num=8   [s[i]-'a']=0 map=0
   [function] L=40 :s[2] = g, num=6   [s[i]-'a']=0 map=0
   [function] L=40 :s[3] = h, num=7   [s[i]-'a']=0 map=0
   [function] L=40 :s[4] = t, num=19  [s[i]-'a']=0 map=0
   [function] L=40 :s[0] = o, num=14  [s[i]-'a']=1 map=0
   [function] L=40 :s[1] = n, num=13  [s[i]-'a']=1 map=0
   [function] L=40 :s[2] = e, num=4   [s[i]-'a']=1 map=0
   [function] L=40 :s[0] = t, num=19  [s[i]-'a']=0 map=0
   [function] L=40 :s[1] = h, num=7   [s[i]-'a']=0 map=0
   [function] L=40 :s[2] = r, num=17  [s[i]-'a']=0 map=0
   [function] L=40 :s[3] = e, num=4   [s[i]-'a']=0 map=0
   [function] L=40 :s[4] = e, num=4   [s[i]-'a']=0 map=0
   [function] L=40 :s[0] = f, num=5   [s[i]-'a']=0 map=0
   [function] L=40 :s[1] = i, num=8   [s[i]-'a']=0 map=0
   [function] L=40 :s[2] = v, num=21  [s[i]-'a']=0 map=0
   [function] L=40 :s[3] = e, num=4   [s[i]-'a']=0 map=0
   [function] L=40 :s[0] = s, num=18  [s[i]-'a']=0 map=0
   [function] L=40 :s[1] = e, num=4   [s[i]-'a']=0 map=0
   [function] L=40 :s[2] = v, num=21  [s[i]-'a']=0 map=0
   [function] L=40 :s[3] = e, num=4   [s[i]-'a']=0 map=0
   [function] L=40 :s[4] = n, num=13  [s[i]-'a']=0 map=0
   [function] L=40 :s[0] = n, num=13  [s[i]-'a']=0 map=0
   [function] L=40 :s[1] = i, num=8   [s[i]-'a']=0 map=0
   [function] L=40 :s[2] = n, num=13  [s[i]-'a']=0 map=0
   [function] L=40 :s[3] = e, num=4   [s[i]-'a']=0 map=0
   [main] L=103 :--> 012
**/
