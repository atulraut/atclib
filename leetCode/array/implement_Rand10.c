/***
    https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/552/week-4-august-22nd-august-28th/3439/
    Given the API rand7() that generates a uniform random integer in the range [1, 7],
    write a function rand10() that generates a uniform random integer in the range [1, 10].
    You can only call the API rand7(), and you shouldn't call any other API. Please do
    not use a language's built-in random API.
    Each test case will have one internal argument n, the number of times that your implemented function
    rand10() will be called while testing. Note that this is not an argument passed to rand10().
Follow up:
    What is the expected value for the number of calls to rand7() function?
    Could you minimize the number of calls to rand7()?
    Logic : https://www.youtube.com/watch?v=BvYd6KSW4nQ

 */

#include "../at_lib.h"


// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7
int rand7(){
   return 1 + rand() % 7;
}

int rand10() {
    int v1, v2;
    v1 = rand7();
    v2 = rand7();
    while (v1 > 5)
      v1 = rand7();
    while (v2 == 7)
      v2 = rand7 ();
    return (v2 <= 3) ? v1 : v1 + 5;
}

int main() {

  for (int i=0; i<100; i++)
    printf("[%s-%d]  rand10 = %d \n",__func__,i, rand10());

    return 0;
}

