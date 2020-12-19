/**
  1446. Consecutive Characters :
  Given a string s, the power of the string is the maximum length of a non-empty
  substring that contains only one unique character.
  Return the power of the string.
  Example 1:
  Input: s = "leetcode"
  Output: 2
  Explanation: The substring "ee" is of length 2 with the character 'e' only.
  Example 2:
  Input: s = "abbcccddddeeeeedcba"
  Output: 5
  Explanation: The substring "eeeee" is of length 5 with the character 'e' only.
  Example 3:
  Ref : https://leetcode.com/problems/consecutive-characters/
*/

#include <stdio.h>
#include <stdlib.h>

int maxPower(char * s){
    int max=1;
    int curr=1;
    for(int i=1; s[i]; ++i){
        if(s[i]==s[i-1]) {
            curr++;
            if(curr>max)
	      max=curr;
        } else
	  curr=1;
    }
    return max;
}

int main () {
  char arr[] = "leetcode";
  int ret = 0;
  printf ("[%s] op = %d \n", __func__, maxPower(arr));
  return 0;
}
