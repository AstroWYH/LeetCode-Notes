哈希 map

思路：遍历数组，用unordered_map记录<nums元素, idx>，然后一边遍历，一边查询unordered_map内是否
已经存在target-元素，如果存在则返回结果索引<“元素i”的位置, “target-元素”的位置>。

注：此题为何不用双指针？因此双指针靠拢一般要排序，但此题最后要返回索引，排序了还咋返回索引。
注：题干存在“找出”关键词，并返回下标，通过这点应该想到哈希map记录。
注：又使用了unordered_map的常见用法，即一边用来“存”“记录元素,idx等”，一般“find”“查询”“target-元素”。
注：for()内再用unordered_map.find()实际上没任何问题，因为哈希结构的unordered_map查询、增删一般是
O(1)复杂度，不会带来影响。

1：元素遍历后插入unordered_map，如果该处放在for()刚开始处，就会出现find()老是查到自己的问题，
比如{3,3}，第1个3插入unordered_map后，find()直接把自己找到了，返回{0,0}，此时不满足题意，需要注意。

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> unmap;
        for (int i = 0; i < nums.size(); i++) {
            auto it = unmap.find(target - nums[i]);
            if (it != unmap.end() && i != it->second) {
                return {i, it->second};
            }
            unmap[nums[i]] = i; // wyh 1
        }
        return {0, 0};
    }
};