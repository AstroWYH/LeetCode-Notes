数组 排序 快速排序 堆排序

注：后续补充将“快排+堆排”写法补充一遍。

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return a > b;
        });
        return nums[k - 1];
    }
};