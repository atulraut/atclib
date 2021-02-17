/***
    LeetCode : Edit Distance

    Given two strings word1 and word2, return the minimum number of
    operations required to convert word1 to word2.

    You have the following three operations permitted on a word:

    Insert a character
    Delete a character
    Replace a character

    Example 1:
    Input: word1 = "horse", word2 = "ros"
    Output: 3
    Explanation:
    horse -> rorse (replace 'h' with 'r')
    rorse -> rose (remove 'r')
    rose -> ros (remove 'e')

    Example 2:
    Input: word1 = "intention", word2 = "execution"
    Output: 5
    Explanation:
    intention -> inention (remove 't')
    inention -> enention (replace 'i' with 'e')
    enention -> exention (replace 'n' with 'x')
    exention -> exection (replace 'n' with 'c')
    exection -> execution (insert 'u')

    Constraints:

    0 <= word1.length, word2.length <= 500
    word1 and word2 consist of lowercase English letters.

    https://leetcode.com/problems/edit-distance/
    Date : 1-24-01 {Palindrome}
    San Deigo, CA

    Algo :
    https://www.youtube.com/watch?v=AuYujVj646Q
    https://www.youtube.com/watch?v=We3YDTzNXEk&t=323s
*/

#include <stdio.h>
#include "../../at_lib.h"

/***
    8MS
*/

// Utility function to find the minimum of three numbers
int min(int a,int b, int c){
  int temp;
  temp = a<b?a:b;
  temp = temp<c?temp:c;
  return temp;
}

int minDistance(char * word1, char * word2){
  // Create a table to store results of subproblems
  int m = strlen(word1);
  int n = strlen(word2);
  int dp[m + 1][n + 1];

  // Fill d[][] in bottom up manner
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      // If first string is empty, only option is to
      // insert all characters of second string
      if (i == 0)
	dp[i][j] = j; // Min. operations = j

      // If second string is empty, only option is to
      // remove all characters of second string
      else if (j == 0)
	dp[i][j] = i; // Min. operations = i

      // If last characters are same, ignore last char
      // and recur for remaining string
      else if (word1[i - 1] == word2[j - 1])
	dp[i][j] = dp[i - 1][j - 1];

      // If the last character is different, consider all
      // possibilities and find the minimum
      else
	dp[i][j] = 1 + min(dp[i][j - 1], // Insert
			   dp[i - 1][j], // Remove
			   dp[i - 1][j - 1]); // Replace
    }
  }

  return dp[m][n];
}

/***
    0 MS
*/
int minDistance2(char * word1, char * word2){

  int m = strlen(word2);
  char *s1 = word1;
  char *s2 = word2;

  int *mat = malloc(sizeof(int) * (m+1));

  for(int i=0; i<=m; ++i) {
    mat[i] = i;
  }

  for(int i=1; *s1; ++i, ++s1) {
    s2 = word2;
    int pre = i-1;
    mat[0] = i;
    for(int j=1; j<=m; ++s2, ++j) {
      int tmp = mat[j];
      int min = *s2 == *s1 ? pre : pre+1;
      min = min < mat[j-1]+1 ? min : mat[j-1]+1;
      mat[j] = mat[j]+1 < min ? mat[j]+1 : min;
      pre = tmp;
    }
  }

  return mat[m];


}

int main () {
  char word1[] = "horse";
  char word2[] = "ros";

  int ret =  minDistance(word1, word2);

  debug ("O/P = %d", ret);
  return 0;
}

/***
    Approach 1: Dynamic Programming

    The idea would be to reduce the problem to simple ones. For example,
    there are two words, horse and ros and we want to compute an edit distance D
    for them. One could notice that it seems to be more simple for short words
    and so it would be logical to relate an edit distance D[n][m] with
    the lengths n and m of input words.

    Let's go further and introduce an edit distance D[i][j] which is an edit
    distance between the first i characters of word1 and the first j characters of word2

    It turns out that one could compute D[i][j], knowing D[i - 1][j], D[i][j - 1] and D[i - 1][j - 1].

    There is just one more character to add into one or both strings and the
    formula is quite obvious.

    If the last character is the same, i.e. word1[i] = word2[j] then

    D[i][j]=1+min⁡(D[i−1][j],D[i][j−1],D[i−1][j−1]−1) D[i][j] = 1 + \min(D[i - 1][j], D[i][j - 1], D[i - 1][j - 1] - 1) D[i][j]=1+min(D[i−1][j],D[i][j−1],D[i−1][j−1]−1)

    and if not, i.e. word1[i] != word2[j] we have to take into account the
    replacement of the last character during the conversion.

    D[i][j]=1+min⁡(D[i−1][j],D[i][j−1],D[i−1][j−1]) D[i][j] = 1 + \min(D[i - 1][j], D[i][j - 1], D[i - 1][j - 1]) D[i][j]=1+min(D[i−1][j],D[i][j−1],D[i−1][j−1])

    So each step of the computation would be done based on the
    previous computation, as follows:

    The obvious base case is an edit distance between the empty string and
    non-empty string that means D[i][0] = i and D[0][j] = j.

    Now we have everything to actually proceed to the computations

    Complexity Analysis

    Time complexity : O(mn) as it follows quite
    straightforward for the inserted loops.
    Space complexity : O(mn) since at each step we
    keep the results of all previous computations.

    => ./a.out
    [main] L=134 :O/P = 3
*/

/***
    Insert : (m, n-1) + 1
    Remove : (m-1, n) + 1
    Replace: (m-1, n-1) + 1

                        Up (is Remove)
			|
			|
     Daigonal(Replace)  |
			|
     Left --------------- (is Insert)
 */
