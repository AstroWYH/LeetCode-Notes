哈希 map

思路：两层for()遍历nums1和nums2，利用unordered_map记录<nums1和nums2的和，该和出现的次数>；
然后两层for()遍历nums3和nums4，用unordered_map查找0-nums1和nums2的和，如果查得到，则返回结果
累加之前记录的“nums1和nums2的和出现的次数”，这是因为其多出现一次，就多一种组合。

注：4个数相加，不是n个数相加，因此这个4是有说法的，因此属于某种具体情况，考虑解法也应该考虑这个4。
比如此题解法就将“4for()拆成了2for()+2for()”。

注：容易想到暴力解法是O(n4)的复杂度，因此不要妄想将其降到O(n)，最终此题解法“对半分”降成O(n²)是比较合理的。

注：题干最终求的是“出现次数”，不是具体有哪些组合，实际上这是降低了难度，要看到这点。根据“出现次数”，
需要想到“哈希map”，map一半时候用来“记录”“存”出现次数，另一半时候用来“find”“取”对应的结果，如此题中的
“0 - (n3 + n4)”，这是map常见的用法之一。

class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> un_map;
        int count = 0;
        for (auto &n1 : nums1) {
            for (auto &n2 : nums2) {
                un_map[n1 + n2]++;
            }
        }
        for (auto &n3 : nums3) {
            for (auto &n4 : nums4) {
                if (un_map.find(0 - (n3 + n4)) != un_map.end()) {
                    count += un_map[0 - (n3 + n4)];
                }
            }
        }
        return count;
    }
};