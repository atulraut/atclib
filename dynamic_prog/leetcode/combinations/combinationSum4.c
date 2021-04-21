/***
	https://leetcode.com/problems/combination-sum-iv/
*/
int combinationSum4(int* nums, int numsSize, int target) {
if(target == 0)
    {
        return 1;
    }

    unsigned long long* dp = (int*)calloc(target+1,sizeof(unsigned long long));
    dp[0] = 1;

    for(int i=1;i<=target;i++)
    {
        for(int j=0;j<numsSize;j++)
        {
            if(nums[j]<=i)
            {
                dp[i] += dp[i-nums[j]];
            }
        }
    }

    return (int)dp[target];

}
