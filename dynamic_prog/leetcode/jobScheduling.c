/***
    Maximum Profit in Job Scheduling
    We have n jobs, where every job is scheduled to be done from
    startTime[i] to endTime[i], obtaining a profit of profit[i].

    You're given the startTime, endTime and profit arrays, return
    the maximum profit you can take such that there are no two jobs
    in the subset with overlapping time range.

    If you choose a job that ends at time X you will be able to start
    another job that starts at time X.

    Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
    Output: 120
    Explanation: The subset chosen is the first and fourth job.
    Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

    Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
    Output: 150
    Explanation: The subset chosen is the first, fourth and fifth job.
    Profit obtained 150 = 20 + 70 + 60.

    Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
    Output: 6

    Constraints:
    1 <= startTime.length == endTime.length == profit.length <= 5 * 104
    1 <= startTime[i] < endTime[i] <= 109
    1 <= profit[i] <= 104

    https://leetcode.com/problems/maximum-profit-in-job-scheduling/

    Date: 28 August 2021.
    Fair Oaks, CA.
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
#define MAX(A, B)   (A>B ? A:B)

struct jobs_data {
  int start;
  int end;
  int profit;
};

/* Global data */
struct jobs_data *jobs;
int *memo;

int compare(const void *p1, const void *p2) {
  struct jobs_data *x1, *x2;
  x1 = (struct jobs_data *)p1;
  x2 = (struct jobs_data *)p2;
  return x1->start - x2->start;
}

int findNextIndex(struct jobs_data *jobs, int size, int index) {
  int time = jobs[index].end;
  for(int i = index; i<size; ++i) {
    if(time <= jobs[i].start)
      return i;
  }
  return size;
}

int maxProfit(struct jobs_data *jobs, int *startTimes, int size, int index) {
  if(index == size)
    return 0;

  if(memo[index] != -1)
    return memo[index];

  int nextIndex = findNextIndex(jobs, size, index);
  int profit_posn = jobs[index].profit + maxProfit(jobs, startTimes, size, nextIndex);
  int profit_nxt =  maxProfit(jobs, startTimes, size, index+1);
  int profit = MAX(profit_posn, profit_nxt);
  return memo[index] = profit;

}

int jobScheduling(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int* profit, int profitSize) {

  memo = (int *)malloc(sizeof(int)*profitSize);
  for(int i = 0; i < profitSize; ++i) {
    memo[i] = -1;
  }

  jobs = (struct jobs_data *)malloc(sizeof(struct jobs_data)*profitSize);

  for(int i = 0; i < profitSize; ++i) {
    jobs[i].start = startTime[i];
    jobs[i].end = endTime[i];
    jobs[i].profit = profit[i];
  }

  qsort(jobs, profitSize, sizeof(struct jobs_data), compare);

  int *startTimes;
  startTimes = (int *)malloc(sizeof(int)*profitSize);
  for(int i = 0; i < profitSize; ++i)
    startTimes[i] = jobs[i].start;

  return maxProfit(jobs, startTimes, profitSize, 0);

}

int main (int argc, char **argv) {
  int ret = 0;

  int startTime[] = {1,2,3,3};
  int startTimeSize = sizeof(startTime)/sizeof(startTime[0]);
  int endTime[] = {3,4,5,6};
  int endTimeSize = sizeof(endTime)/sizeof(endTime[0]);
  int profit[] = {50,10,40,70};
  int profitSize = sizeof(profit)/sizeof(profit[0]);

  ret = jobScheduling(startTime, startTimeSize, endTime, endTimeSize, profit, profitSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=129 :Output = 120
**/
