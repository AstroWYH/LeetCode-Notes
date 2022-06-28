动态规划

思路：稍加思考发现常规思路不好做后，就考虑动态规划。另外，此题还有“动归+二分法”的解法，需要将“二分法”
理解到极致，后续可补充思考。

动归五部曲：
1：确定dp数组及下标的含义。
dp[i]：代表在nums中，以nums[i]结尾的最长子序列长度。
可见，一般dp[i]都直接设为题干想求的问题，此题也一样。dp[i]的i从0~n-1递推，到n-1时dp[n-1]为答案。

2：确定递推公式。(思考转移方程)
设j∈[0,i)，考虑每轮计算新dp[i]时，遍历j~[0,i)列表区间。即2层for()，第1层遍历i~[0,n-1]，第2层遍历j~[0,i)。
1）当nums[i]>nums[j]时：nums[i]可以接在nums[j]之后（此题严格递增），此情况下，最长上升子序列为dp[j]+1。
此外，上述遍历j~[0,i)过程中，可能会遇到dp[j]+1时大时小的情况，我们需要“积累dp[j]+1的最大值”，因此递推公式为：
dp[i]=max(dp[i],dp[j]+1)。这点不容易思考，可画图细推。
2）当nums[i]<=nums[j]时：nums[i]无法接在nums[j]之后，此情况上升子序列不成立，跳过。

3：初始化dp数组。dp[i]所有元素置1，每个元素都至少可以单独成为子序列，此时长度都为1。
从1开始“积累”，可见，dp数组的初始化，并不一定是dp[0]、dp[1]这样的初始化，要充分考虑，可能整个dp[]都能初始化。

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<int> dp(nums.size(), 0);
        for (int i = 0; i < nums.size(); ++i) {
            dp[i] = 1; // 此处初始化，积累过程从1开始
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1); // 这里max(dp[i],...)的dp[i]最难理解，画图思考
                }
            }
        }
        // for(auto &v : dp) {
        //     cout << v<<endl; // 打印dp数组
        // }
        return *max_element(dp.begin(), dp.end());
    }
};