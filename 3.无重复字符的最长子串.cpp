滑动窗口 快慢双指针 字符串 最长

思路：滑动窗口经典题之一。需要想到，如“abaccd”，快指针在走到“后重复字符”时，慢指针应当一直往前走，直到跨过“前重复字符”。

注：滑动窗口，快慢双指针题型，需要记住类似模板。快指针遍历for()中fast++，慢指针在while()或if()有条件地slow++。
最长或最短的ans，在此过程中收集结果。
注：如何实现思路？怎么记录这个“滑动窗口”？因为fast每走一步都需要知道“前面是否重复”，应该联想到用unordered_set的find()，
因为复杂度为O(1)不消耗，这点需要能想到。

注：slow++的条件while()和if()是难点，也是解题思路的实现，总结经验此题是while()中set.erase()，slow++。
注：ans在什么时候记录更新，也是难点，此题仅在for()每次遍历中记录更新。“可以考虑放在for()最前还是最后合理”。
注：此题明确每个fast都set.insert()，这更像是“真正的滑动窗口”，fast每遍历一个set.insert()，每重复时不断set.erase()。

注：有的题“滑动窗口”仅靠fast、slow体现，此题还通过“unordered_set的增长缩短”体现。

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() <= 1) return s.length();
        int slow = 0, fast = 0;
        int diff = INT_MIN, ans = 0;
        unordered_set<int> set;
        for (; fast < s.length(); fast++) {
            while (set.find(s[fast]) != set.end()) {
                set.erase(s[slow]);
                slow++;
            }
            diff = fast - slow + 1;
            ans = max(ans, diff);
            set.insert(s[fast]);
        }
        return ans;
    }
};