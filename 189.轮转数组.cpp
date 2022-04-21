空间复杂度o(n)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> newArray(n);
        for (size_t i = 0; i < n; i++) {
            newArray[(i + k) % n] = nums[i]; // wyh 这里是核心, 可以记住, i+k对n求模, 就能直接得到正确的数组位置
        }
/*         for (size_t i = 0; i < n); i++) {
            nums[i] = newArray[i];
        } */
        nums.assign(newArray.begin(), newArray.end());
    }
};


空间复杂度o(1)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size(); // wyh 主要考虑k > nums.size()的情况
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
