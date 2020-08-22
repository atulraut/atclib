#include <stdio.h>
#include <stdlib.h>

/*
Problem: Subarray Sum Equals K Using C.
Given an array of integers and an integer k, you need to find the total number of continuous
subarrays whose sum equals to k.
Example 1:
Input:nums = [1,1,1], k = 2
Output: 2
Note:
    The length of the array is in range [1, 20,000].
    The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].

Approach : Using Hash map
Algorithm:
The idea behind this approach is as follows: If the cumulative sum(repreesnted by sum[i]
for sum upto i (ith index) upto two indices is the same, the sum of the elements lying in
between those indices is zero. Extending the same thought further, if the cumulative sum upto two
indices, say i and j is at a difference of k
i.e. if sum[i] − sum[j] = k, the sum of elements lying between
indices i and j is k.

Based on these thoughts, we make use of a hashmap map which is used to store the cumulative
sum upto all the indices possible along with the number of times the same sum occurs. We store the
data in the form: (sum i, no.ofoccurences of sum i).
We traverse over the array nums and keep on finding the cumulative sum. Every time we
encounter a new sum, we make a new entry in the hashmap corresponding to that sum. If the same
sum occurs again, we increment the count corresponding to that sum in the hashmap. Further, for
every sum encountered, we also determine the number of times the sum sum−k has occured
already, since it will determine the number of times a subarray with sum k has occured upto the
current index. We increment the countcountcount by the same amount.

After the complete array has been traversed, the count gives the required result.

Time complexity : O(n). The entire numsnumsnums array is traversed only once.
Space complexity : O(n). Hashmap mapmapmap can contain upto nnn distinct entries in the worst case.

Ref:
https://leetcode.com/problems/subarray-sum-equals-k/solution/
https://www.youtube.com/watch?v=HbbYPQc-Oo4
*/

struct node {
    int key;
    int val;
    struct node *next;
};

struct table {
    int size;
    struct node **list;
};

struct table *createTable(int size) {
    struct table *t = (struct table*)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node**)malloc(sizeof(struct node*)*size);
    int i;
    for(i=0;i<size;i++)
        t->list[i] = NULL;
    return t;
}

int hashCode(struct table *t,int key) {
    if(key<0)
        return -(key%t->size);
    return key%t->size;
}

void insert(struct table *t,int key) {
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];

    printf ("[%s] 1] pos=%d key=%d list = %p L=%d\n",__func__, pos, key, list, __LINE__);

    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    struct node *temp = list;

    while(temp) {
        if(temp->key==key) {
            temp->val++;
            printf ("[%s] temp = %p key=%d val=%d L=%d\n",__func__, temp, temp->key, temp->val, __LINE__);
            return;
        }
        temp = temp->next;
    }

    newNode->key = key;
    newNode->val = 1;
    newNode->next = list;
    t->list[pos] = newNode;

    printf ("[%s] newNode = %p key=%d val=%d L=%d\n",__func__, newNode, newNode->key, newNode->val, __LINE__);
}

int lookup(struct table *t, int key) {
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    printf ("[%s] 1] pos=%d key=%d list = %p L=%d\n",__func__, pos, key, list, __LINE__);
    struct node *temp = list;
    while(temp) {
        printf ("[%s] 2] temp->key = %d L=%d \n",__func__, temp->key, __LINE__);
        if(temp->key==key){
           temp->val++;
	   printf ("[%s] 2.1] temp->key = %d val=%d L=%d \n",__func__, temp->key, temp->val, __LINE__);
	   return (temp->val);
        }
        temp = temp->next;
    }
    printf ("[%s] 3] key = %d L=%d\n",__func__, key, __LINE__);
    return -1;
}

int subarraySum(int* nums, int numsSize, int k) {

    struct table *t = createTable(numsSize);
    int sum=0,count=0,n;

    insert(t,0);
    for(int i=0; i<numsSize; i++) {
        sum+=nums[i];

	printf ("[%s] i = %d sum=%d (sum-k)=%d L=%d\n",__func__, i, sum, (sum-k), __LINE__);
        if((n=lookup(t, sum-k))!=-1) {
           count++;
           printf ("[%s] i = %d cnt=%d L=%d\n",__func__, i, count, __LINE__);
        }
        insert(t,sum);
    }

    return count;
}


int main() {
    int arr[] = {10, 2, -2, -20, 10};
    int key = 10;
    int cnt = subarraySum(arr, 5, key);
    printf("Occurances of subarray of val=%d is = %d \n",key, cnt);

    return 0;
}

/*
-------------------------------------
Key=10
-------------------------------------
10  2  -2 -20  10       : Input
-------------------------------------
10  12 10 -10  0        : SUM_Prefix
-------------------------------------
0   1  2   3   4        : Index
-------------------------------------
1      2       3        : Count
-------------------------------------
***** MAP ***************************
-------------------------------------
sum  | val/count
-------------------------------------
10   | 1
12   | 1
10   | 2
-10  | 1
0    | 1
-------------------------------------

Output:
=> ./a.out
[insert] 1] pos=0 key=0 list = (nil) L=75
[insert] newNode = 0x830470 key=0 val=1 L=94
[subarraySum] i = 0 sum=10 (sum-k)=0 L=122
[lookup] 1] pos=0 key=0 list = 0x830470 L=100
[lookup] 2] temp->key = 0 L=103 [insert] 1] pos=0 key=10 list = 0x830470 L=75
[insert] newNode = 0x830490 key=10 val=1 L=94
[subarraySum] i = 1 sum=12 (sum-k)=2 L=122
[lookup] 1] pos=2 key=2 list = (nil) L=100
[lookup] 3] key = 2 L=109
[insert] 1] pos=2 key=12 list = (nil) L=75
[insert] newNode = 0x8304b0 key=12 val=1 L=94
[subarraySum] i = 2 sum=10 (sum-k)=0 L=122
[lookup] 1] pos=0 key=0 list = 0x830490 L=100
[lookup] 2] temp->key = 10 L=103 [lookup] 2] temp->key = 0 L=103 [insert] 1] pos=0 key=10 list = 0x830490 L=75
[insert] temp = 0x830490 key=10 val=2 L=83
[subarraySum] i = 3 sum=-10 (sum-k)=-20 L=122
[lookup] 1] pos=0 key=-20 list = 0x830490 L=100
[lookup] 2] temp->key = 10 L=103 [lookup] 2] temp->key = 0 L=103 [lookup] 3] key = -20 L=109
[insert] 1] pos=0 key=-10 list = 0x830490 L=75
[insert] newNode = 0x8304f0 key=-10 val=1 L=94
[subarraySum] i = 4 sum=0 (sum-k)=-10 L=122
[lookup] 1] pos=0 key=-10 list = 0x8304f0 L=100
[lookup] 2] temp->key = -10 L=103 [insert] 1] pos=0 key=0 list = 0x8304f0 L=75
[insert] temp = 0x830470 key=0 val=4 L=83
Occurances of subarray of val=10 is = 3
*/
