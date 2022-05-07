哈希 set 数组

思路：此题完全是利用unordered_set的“去重”特性完成，首先需要对vec nums1转换成unordered_set nums1，
此时内部已去重，然后遍历vec nums2，对每个vec nums2的元素都去unordered_set nums1中进行find，因为
unordered_set查询效率是O(1)，这样一旦find成功就用result_set记录（原因仍然是怕重复），最后转换回vec。

注：需要熟练运用unordered_set的“去重”特性；
注：需要了解unordered_xxx查询和增删时间复杂度O(1)的特点，否则此题复杂度为O(n²)，和暴力解法无区别；
注：需要熟练运用vector和unordered_set之间的拷贝构造初始化、转换。vector转unordered_set会自动去重，
unordered_set转vector会原封不动。

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> result_set;
        unordered_set<int> set(nums1.begin(), nums1.end());
        for (auto &n : nums2) {
            if(set.find(n) != set.end()) {
                result_set.insert(n);
            }
        }
        return vector<int>(result_set.begin(), result_set.end());
    }
};