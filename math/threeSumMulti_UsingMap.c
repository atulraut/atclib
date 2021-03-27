/***
    923. 3Sum With Multiplicity
    https://leetcode.com/problems/3sum-with-multiplicity/solution/

    Given an integer array arr, and an integer target, return the
    number of tuples i, j, k such that i < j < k and arr[i] + arr[j] + arr[k] == target.

    As the answer can be very large, return it modulo 109 + 7.

    Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
    Output: 20
    Explanation:
    Enumerating by the values (arr[i], arr[j], arr[k]):
    (1, 2, 5) occurs 8 times;
    (1, 3, 4) occurs 8 times;
    (2, 2, 4) occurs 2 times;
    (2, 3, 3) occurs 2 times.

    Input: arr = [1,1,2,2,2,2], target = 5
    Output: 12
    Explanation:
    arr[i] = 1, arr[j] = arr[k] = 2 occurs 12 times:
    We choose one 1 from [1,1] in 2 ways,
    and two 2s from [2,2,2,2] in 6 ways.

    Constraints:
    3 <= arr.length <= 3000
    0 <= arr[i] <= 100
    0 <= target <= 300

    Date : 27 March 2021
    San Diego, CA.
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

int C(int n,int k){
    long long temp=1;
    if(k==1)    temp=n;
    if(k==2)    temp=(n%1000000007)*((n-1)%1000000007)/2;
    if(k==3)    temp=(long long)((n%1000000007)*((n-1)%1000000007))%1000000007*((n-2)%1000000007)/3/2;
    return temp%1000000007;
}

int threeSumMulti(int* arr, int arrSize, int target){
    int *map=(int *)calloc(sizeof(int),101);
    for(int i=0;i<arrSize;i++){
        map[arr[i]]++;
    }
    int target2,ans=0;
    for(int i=0;i<=target/2&&i<=100;i++){
        if(map[i]<=0)       continue;
        target2=target-i;
        map[i]--;
        for(int j=i;j<=target2/2&&j<=100;j++){
            if(map[j]<=0)   continue;
            map[j]--;
            int k=target2-j;
            if(k>100||k<0){
                map[j]++;
                continue;
            }
            if(map[k]<=0){
                map[j]++;
                continue;
            }
            else if(k>=j){
                map[j]++;
                if(i!=j&&j!=k&&i!=k)    ans+=C(map[i]+1,1)*C(map[j],1)*C(map[k],1);
                if(i==j&&j!=k&&i!=k)    ans+=C(map[i]+1,2)*C(map[k],1);
                if(i!=j&&j!=k&&i==k)    ans+=C(map[i]+1,2)*C(map[j],1);
                if(i!=j&&j==k&&i!=k)    ans+=C(map[i]+1,1)*C(map[j],2);
                if(i==j&&j==k&&i==k)    ans+=C(map[i]+1,3);
            }
        }
        map[i]++;
    }
    return ans;
}


int main () {
  int arr[] = {1,1,2,2,3,3,4,4,5,5};
int target = 8;
int arrSize = sizeof(arr)/sizeof(arr[0]);

int output = threeSumMulti(arr, arrSize, target);
debug ("output = %d ", output);

return 0;
}

/**
   For Algo : Check Daigram.
 **/
/**
  => ./a.out
  [main] L=136 :output = 20
 **/

