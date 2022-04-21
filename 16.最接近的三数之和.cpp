解题思路
双指针（类似15.三数之和）
核心思想：
1）考虑边界问题，小于3个数不考虑
2）升序排序一遍数组，时间复杂度o(logn)
3）用i遍历数组，i+l+r首位双指针的三数之和sum，和target进行比较，找最接近target的sum
对每个i，l和r都逐渐靠拢查询，时间复杂度o(n²)
对每个i，l<r时一直while循环查找，否则跳出循环i++
对每个i， sum<target则l++，sum>target则r--，相等则直接返回sum
对每个i，对每次已确定的l、r，记录当前的sum和target差值，并选择更新minValue
对每个i，对每次已确定的l、r，用map记录下[minValue, sum]
遍历完所有i后，找出map中记录的minValue对应的sum

#include <cstdlib> 
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() <= 2) {
            return 0;
        }
        sort(nums.begin(), nums.end());
        int minValue = INT_MAX;
        map<int, int> min_sum_map;
        for (int i = 0; i < nums.size() - 1; i++) {
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < target) {
                    left++;
                } else if (sum > target) {
                    right--;
                } else {
                    return sum;
                }
                if (abs(sum - target) < minValue) {
                    minValue = abs(sum - target);
                    min_sum_map[minValue] = sum;
                }
            }
        }
        auto it = min_sum_map.find(minValue);
        if (it != min_sum_map.end()) {
            return min_sum_map[minValue];
        } else {
            return 0;
        }
    }
};