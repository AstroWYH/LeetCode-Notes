// 本题3个变量，思路为遍历数组i的基础上用双指针，o(n2), 快排:o(logn) + 遍历数组i:o(n) * 双指针:o(n)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() <= 2) { // 边界判断，vec小于3，直接返回空
            return {};
        }
        sort(nums.begin(), nums.end()); // 先对nums进行排序，这样才方便后续的操作，时间复杂度为独立的o(logn)
        vector<vector<int>> result;
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1]) { // 在遍历i的过程中，滤除重复大小的nums[i]，且最好用i - 1，避免i出现越界问题
                continue; // 跳出本轮循环，记得不是break!!!
            }
            if (nums[0] > 0) { // 如果排序后的第1个元素都比0大，那3个加起来不可能等于0
                return {};
            }
            int left = i + 1; // 定界，对每一个i，left、right分别为i右边的左右边界双指针，且循环依次靠拢
            int right = nums.size() - 1;
            while (left < right) {
                if (nums[i] + nums[left] + nums[right] == 0) {
                    result.push_back({nums[i], nums[left], nums[right]}); // 满足要求，直接放到二维vec的返回值框框里
                    while (left < right && nums[left] == nums[left + 1]) { // 由于满足要求了，所以要滤除重复大小的nums[left]、nums[right]
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    left++; // 由于上次已经满足，且旁边又没有重复，只一个靠拢肯定不对，left++就会大于0，right又得--，所以同时靠近
                    right--;
                }
                else if (nums[i] +nums[left] + nums[right] < 0) { // nums[i]是固定的，值小了，说明应该left++
                    left++;
                }
                else {
                    right--;
                }
            }
        }
        return result;
    }
};