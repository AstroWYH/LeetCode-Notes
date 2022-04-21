// 明天写题解
// https://www.bilibili.com/video/BV1V44y1s7zJ?spm_id_from=333.1007.top_right_bar_window_custom_collection.content.click
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