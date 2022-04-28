贪心算法or动态规划

思路（贪心算法）：画出股票走势折线图，然后会发现（需要脑筋急转弯）每个递增的小区间为局部最优，
所有的递增小区间加起来为全局最优。所有的递增区间的股票价格全部加起来，就是最赚的。

注：结合此题和之前的提可逐步发现，贪心算法的题都有个巧妙的核心，需要能够想到。
，遍历一层for循环，在遍历过程中注重“收集”的过程，每一次收集都体现一次“局部”，
将遍历完所有的“收集”叠加在一起，体现“全局”。

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sum = 0, n = prices.size();
        for(int i = 0; i < n - 1; i++) {
            if (prices[i + 1] - prices[i] > 0) {
                sum += prices[i+1] - prices[i];
            }
        }
        return sum;
    }
};