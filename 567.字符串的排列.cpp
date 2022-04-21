滑动窗口 字符串
核心思想：s1短，s2长，拿s1的长度作为滑动窗口，遍历整个s2

思路：此题有个关键，n1长度内字符串，只需要种类相同，个数相同，s1就是s2的字串，不要求字母排序相同

思路1：很容易想到用map把s1装起来，但是很快发现复杂度需要n1×n2至少
思路2：所以此题的题解思路，vec(26)把26个字母按照idx为ascii码值存储，理解vec1[s1[i] - 'a']，则vec{1,1,1,0,0,...}，
表示字符串'abc'，有字母进来就更新vec，相当于一种另类的map（key值已经天然排序好了），因为本题跟字母排序无关，只需要count计数，
这样，'abc'和'bac'都拥有相同的vec{1,1,1,0,0,...}，将'abc'或'bac'转换成排序无关的vec{1,1,1,0,0,...}，此题得解。

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        if (n1 > n2) return false;
        vector<int> vec1(26);
        vector<int> vec2(26);
        for (int i = 0; i < n1; i++) {
            vec1[s1[i] - 'a']++;
            vec2[s2[i] - 'a']++;
        }
        if (vec1 == vec2) return true; 
        for (int i = 1; i + n1 - 1 < n2; i++) {
            vec2[s2[i + n1 - 1] - 'a']++;
            vec2[s2[i - 1] - 'a']--;
            if (vec1 == vec2) return true;
        }
        return false;
    }
};