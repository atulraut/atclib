/***
    Nested List Weight Sum
    https://leetcode.com/problems/nested-list-weight-sum/
    You are given a nested list of integers nestedList. Each element
    is either an integer or a list whose elements may also be integers or other lists.

    The depth of an integer is the number of lists that it is inside of.
    For example, the nested list [1,[2,2],[[3],2],1] has each integer's value set to its depth.

    Return the sum of each integer in nestedList multiplied by its depth.

    Example 1:
    Input: nestedList = [[1,1],2,[1,1]]
    Output: 10
    Explanation: Four 1's at depth 2, one 2 at depth 1. 1*2 + 1*2 + 2*1 + 1*2 + 1*2 = 10.

    Example 2:
    Input: nestedList = [1,[4,[6]]]
    Output: 27
    Explanation: One 1 at depth 1, one 4 at depth 2, and one 6 at depth 3. 1*1 + 4*2 + 6*3 = 27.

    Example 3:
    Input: nestedList = [0]
    Output: 0

    Constraints:
    1 <= nestedList.length <= 50
    The values of the integers in the nested list is in the range [-100, 100].
    The maximum depth of any integer is less than or equal to 50.
    Date : 1-22-21 {Palindrome Date}
    San Diego, CA
*/

#include <stdio.h>
#include "../../at_lib.h"

/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 *
 * *********************************************************************
 */

/**
 *   DFS Using C
 */

struct NestedInteger {
  struct NestedInteger *list;
};

/***
    Initializes an empty nested list and return a reference
    to the nested integer.
*/
struct NestedInteger *NestedIntegerInit() {
  struct NestedInteger *list = (struct NestedInteger *)malloc(sizeof(struct NestedInteger));
  return list;
}

/***
    Return true if this NestedInteger holds a single integer,
    rather than a nested list.
*/
bool NestedIntegerIsInteger(struct NestedInteger *list) {

}

/***
    Return the single integer that this NestedInteger holds,
    if it holds a single integer
    The result is undefined if this NestedInteger holds a nested list
*/
int NestedIntegerGetInteger(struct NestedInteger *list) {

}

/***
    Set this NestedInteger to hold a single integer.
*/
void NestedIntegerSetInteger(struct NestedInteger *ni, int value) {

}

/***
     Set this NestedInteger to hold a nested list and
     adds a nested integer elem to it.
*/
void NestedIntegerAdd(struct NestedInteger *ni, struct NestedInteger *elem) {

}

/***
     Return the nested list that this NestedInteger holds,
     if it holds a nested list
     The result is undefined if this NestedInteger holds a single integer
*/
struct NestedInteger **NestedIntegerGetList(struct NestedInteger *list) {

}

/***
     Return the nested list's size that this NestedInteger holds,
     if it holds a nested list
     The result is undefined if this NestedInteger holds a single integer
*/
int NestedIntegerGetListSize(struct NestedInteger *list) {

}

int cal(struct NestedInteger** list, int size, int depth) {
  int sum = 0;
  for(int i = 0; i < size; i++) {
    struct NestedInteger* ni = list[i];
    if(NestedIntegerIsInteger(ni)) {
      sum += depth * NestedIntegerGetInteger(ni);
    } else {
      sum += cal(NestedIntegerGetList(ni), NestedIntegerGetListSize(ni), depth + 1);
    }
  }

  return sum;
}
int depthSum(struct NestedInteger** nestedList, int nestedListSize){
  int sum = 0;

  sum += cal(nestedList, nestedListSize, 1);
  return sum;
}

int main () {
  struct NestedInteger *nestedList;
  int nestedListSize = 1;

  debug ("Sum = %d", cal(nestedList, nestedListSize, 1));
}

/**
 Complexity Analysis :
 Let NNN be the total number of nested elements in the input list.
 For example, the list [ [[[[1]]]], 2 ] contains 444 nested lists
 and 222 nested integers (111 and 222), so N=6N = 6N=6 for that particular case.

 Time complexity : O(N)\mathcal{O}(N)O(N).

 Recursive functions can be a bit tricky to analyze, particularly when
 their implementation includes a loop. A good strategy is to start by
 determining how many times the recursive function is called, and then
 how many times the loop will iterate across all calls to the recursive function.

 The recursive function, dfs(...) is called exactly once for each nested
 list. As NNN also includes nested integers, we know that the number of
 recursive calls has to be less than NNN.

 On each nested list, it iterates over all of the nested elements
 directly inside that list (in other words, not nested further).
 As each nested element can only be directly inside one list, we
 know that there must only be one loop iteration for each nested element.
 This is a total of NNN loop iterations.

 So combined, we are performing at most 2⋅N2 \cdot N2⋅N recursive calls
 and loop iterations. We drop the 222 as it is a constant, leaving us
 with time complexity O(N)\mathcal{O}(N)O(N).

 Space complexity : O(N)\mathcal{O}(N)O(N).
 In terms of space, at most O(D)O(D)O(D) recursive calls are placed on
 the stack, where DDD is the maximum level of nesting in the input.
 For example, D=2D=2D=2 for the input [[1,1],2,[1,1]], and D=3D=3D=3 for the input [1,[4,[6]]].
 In the worst case, D=ND = ND=N, (e.g. the list [[[[[[]]]]]]) so the
 worst-case space complexity is O(N)O(N)O(N).
**/

