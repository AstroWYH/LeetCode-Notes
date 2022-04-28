class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int slow = 0, fast = 0;
        int sum = 0, ans = INT32_MAX, diff = 0;
        for (; fast < nums.size(); fast++) {
            sum += nums[fast];
            while (sum >= target) {
                diff = fast - slow + 1;
                ans = min(diff, ans);
                sum -= nums[slow];
                slow++;
            }
        }
        if (slow == 0) return 0;
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