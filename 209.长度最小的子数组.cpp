滑动窗口 快慢双指针

思路：经典滑动窗口，快慢双指针题型。for遍历fast，sum累加；当满足一定条件时，slow++，缩减窗口，
同时更新sum和ans。运用标准的滑动窗口模板就行。

注：slow移动的判断条件，如while (sum >= target)，往往不会太过复杂，如果考虑得太过复杂的话，比如
最下面硬想的方法，往往已经陷入误区，应该进一步考虑找到简单有效的判定条件。

1：注意这里的while，slow++会一直进行到不满足条件为止；这里有时是while有时是if，具体情况具体分析。
2：特殊情况，全部都不满足条件，返回0。

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int slow = 0, fast = 0;
        int sum = 0, ans = INT32_MAX, diff = 0;
        for (; fast < nums.size(); fast++) {
            sum += nums[fast];
            while (sum >= target) { // wyh 1
                diff = fast - slow + 1;
                ans = min(diff, ans);
                sum -= nums[slow];
                slow++;
            }
        }
        if (slow == 0) return 0; // wyh 2
        return ans;
    }
};


硬想的解法，其实还是滑动窗口的思想。
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        int fast = 0, slow = 0;
        int distance = 0, ans = n, diff = 0, sum = 0;
        while (fast < n) {
            sum += nums[fast];
            if (sum >= target) {
                distance = fast + 1;
                ans = min(distance, ans);
                diff = sum - target;
                break;
            }
            fast++;
            if (fast == n) return 0;
        }
        while (1) {
            while (diff - nums[slow] >= 0 && slow <= fast) {
                diff -= nums[slow++];
                distance = fast - slow + 1;
                ans = min(distance, ans);
            }
            while (fast < n - 1 && diff - nums[slow] < 0) {
                diff += nums[++fast];
            }
            if (fast == n - 1 && diff - nums[slow] < 0) {
                break;
            }
        }
        return ans;
    }
};