/***
    1641. Count Sorted Vowel Strings

    Given an integer n, return the number of strings of length n that
    consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
    A string s is lexicographically sorted if for all valid i, s[i] is the
    same as or comes before s[i+1] in the alphabet.

    Example 1:
    Input: n = 1
    Output: 5
    Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].

    Example 2:
    Input: n = 2
    Output: 15
    Explanation: The 15 sorted strings that consist of vowels only are
    ["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
    Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.

    Example 3:
    Input: n = 33
    Output: 66045
    Constraints:
    1 <= n <= 50

    Date : 1-20-21 [Palindrome Date]
    San Diego
*/

#include <stdio.h>
#include "../../at_lib.h"

int countVowelStrings(int n) {
  return (n + 4) * (n + 3) * (n + 2) * (n + 1) / 24;
}

int main () {
  debug ("O/p = %d", countVowelStrings(2));
}

/***
    => ./a.out
    [main] L=37 :O/p = 15

    Time Complexity: O(1), as the approach runs in constant time.
    Space Complexity: O(1), as the approach uses constant extra space.
*/

/***
    Approach 4: Bottom Up Dynamic Programming, Tabulation

    This is another approach to solve the Dynamic Programming problems.
    We use the iterative approach and store the result of subproblems
    in bottom-up fashion also known as Tabulation. We store the
    results of previous computations in tabular format and use those results
    for the next computations.

    Algorithm
    We maintain a 2D array , dp of size n*5n where,
    dp[n][vowels] denotes the total number of combinations
    for given n and number of vowels. Using the recurrence
    relation established in Approach 2, we could iteratively calculate the value
    for dp[n][vowels] as,

    dp[n][vowels] = dp[n - 1][vowels] + dp[n][vowels - 1]

    As this is the Bottom Up approach to solve the problem, we must initialize the
    table for the base cases. The base cases are the same as in Approach 2.

    If n=1n = 1n=1, the number of combinations are always equal to number of vowels.
    Hence, we initialize all the values of dp[1][vowels] with vowels.
    If vowels=1vowels = 1vowels=1, the number of combinations are always equal to
    Hence, we initialize all the values of dp[n][1] with 1.

class Solution {
public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(6, 0));
        for (int vowels = 1; vowels <= 5; vowels++)
            dp[1][vowels] = vowels;
        for (int nValue = 2; nValue <= n; nValue++) {
            dp[nValue][1] = 1;
            for (int vowels = 2; vowels <= 5; vowels++) {
                dp[nValue][vowels] =
                    dp[nValue][vowels - 1] + dp[nValue - 1][vowels];
            }
        }
        return dp[n][5];
    }
};
*/
