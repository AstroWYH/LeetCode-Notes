明日写题解

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0 || k == 0) return false;
        map<int, int> count_map;
        if (k >= n) {
            for (int j = 0; j < n; j++) {
                if (++count_map[nums[j]] == 2) {
                    return true;
                }
            }
            return false;
        }
        for (int i = 0; i <= k; i++) {
            if (++count_map[nums[i]] == 2) {
                return true;
            }
        }
        for (int i = k + 1; i < n; i++) {
            --count_map[nums[i - k - 1]];
            if (++count_map[nums[i]] == 2) {
                return true;
            }
        }
        return false;
    }
};

滑动窗口+map，该解法超出时间限制。
时间复杂度为(n-k)k，本以为该复杂度和O(n)差距不大，但比如当k=n/2时，会出现O(n²)的复杂度
/* class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0 || k == 0) return false;
        for (int i = 0; i + k < n; i++) {
            map<int, int> count_map; 
            for (int j = 0; j < k + 1; j++) {
                if (++count_map[nums[i+j]] == 2) {
                    return true;
                }
            }
        }
        if (k >= n) {
            map<int, int> count_map;
            for (int j = 0; j < n; j++) {
                if (++count_map[nums[j]] == 2) {
                    return true;
                }
            }
        }
        return false;
    }
}; */