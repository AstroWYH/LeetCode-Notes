动态规划

思路：动态规划的典型例题。这题一看，就应该是贪心算法或动态规划来解，稍加思索后，
发现问题是“一夜能偷到的最高金额”，即“遍历数组后，这一过程收获的最大值”，考虑dp[i]
表示“遍历到i时的收获的最大值”，然后由于“至少要隔一个偷”，这也“很符合状态转移公式”，
因为会涉及到i-1、i-2之类，就自然而然考虑“动态规划”。

动归五部曲：
1：确定dp数组及下标的含义。dp[i]：遍历数组到i时，当前的能获得的最高金额。
2：确定递推公式。dp[i]=max(dp[i-2]+nums[i],dp[i-1])。要么是前一个(和当前值隔开)，要么是前二个+当前值。
3：初始化dp数组。dp[0]=nums[0]、dp[1]=max(nums[0], nums[1])。
注：因为递推公式涉及到dp[n-1]、dp[n-2]，所以要想到初始化dp[1]、dp[0]。
注：由于要初始化dp[1]、dp[0]，所以for()遍历要从i=2开始。而且边界条件if()需要考虑nums[]长度为0和1时
特殊处理，否则访问dp[0]、dp[1]会出错。

注：此外，可见dp[1]=max(nums[0], nums[1])形如这种不确定的值，也是可以当作“初始化”的，因为在递推过程中，
dp[1]的值就会被计算出来，这不是我们需要太过考虑的事情。

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[nums.size() - 1];
    }
};