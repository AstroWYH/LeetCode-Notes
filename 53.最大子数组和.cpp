贪心算法 or 动态规划

思路：如[-2,1,-3,4,-1,2,1,-7,4]，从头开始遍历，如果自己是负数需要警惕，即自己或自己之前的和是负数，
此时可以sum=0重新计算，因为前面的负数是不做贡献的。从遇到的第1个正数开始累加sum，如果遍历累加过程中，
sum又变为负数，则重新清零，直到遇到下一个正数为止。

注：此题很容易分析成滑动窗口(slow,fast)类型，但是敏锐观察发现slow不满足条件后是跳变到fast,不是slow++
逐次递增，所以考虑是否为贪心算法or动态规划等。
注：sum累加为负后，必须再要跳到下一个正数，否则“耽误”找最大值。
注：核心在于要想到，sum不能累加为负，一旦累加为负就会成为“累赘”，应该“清零”并等待跳到下一个正数重新开始。
注：一般情况下，满足要求的序列两端一定是正数，所以想到要sum从正数开始。
注：遍历到最右端如果遇到如[...,-7,5]，容易出现干扰思想，其实不用管，只要之前的sum-7仍然为正，那么可以
继续囊括[-7,5]，可能会觉得sum变小了不好，其实不重要，因为ans的最大值之前已经记录下来了，即使sum变小了，
它此时也是个正值，会继续给后面做“贡献”（如果后面还有的话）。
注：此题贪心算法解法，sum其实有巧妙之处难以想到，后续学习动态规划看是否可以常规思路解决。

1：学会用INT32_MIN表示最小值。

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT32_MIN; // wyh 1
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            ans = max(sum, ans);
            if (sum <= 0) sum = 0;
        }
        return ans;
    }
};

滑动窗口（快慢双指针）

思路：和上面贪心算法的思路一样。

注：观察可发现slow不满足条件后是跳变到fast,不是slow++逐次递增，所以考虑是否不需要滑动窗口快慢指针，
为其他如贪心算法or动态规划等。
注：slow实际上没起作用，因为没有nums[slow]等。

1：模板这里是while，此题灵活换成if。
2：模板这里是两步，窗口扩大：a)加入fast元素；b)更新当前result值。不一定在这个位置，具体情况具体考虑。

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0, ans = INT32_MIN;
        int slow = 0, fast = 0;
        while (fast < nums.size()) {
            sum += nums[fast];
            ans = max(sum, ans); // wyh 2
            if (sum <= 0 && slow <= fast) // wyh 1
            {
                slow = fast;
                sum = 0;
            }
            fast++;
        }
        return ans;
    }
};
