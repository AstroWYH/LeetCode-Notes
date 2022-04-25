贪心算法

思路：每次遍历“尽量大饼干喂饱大胃口小孩”，核心是两个错落满足的的数组，画出2个数组的图。
每个小孩（遍历对象）从后到前（从大到小），尽量去取大饼干（从后到前）吃，此为局部最优，整个遍历逐渐全局最优。
经考虑，任何一种遍历方式，如“遍历小饼干尽量优先喂小胃口”，或“遍历小胃口尽量优先吃小饼干”，
“估计”都可以解此题。

注：如果小孩太多g>s，则for一直遍历到结束，但是if不会进了，因为饼干没了index不满足，或饼干太小不满足；
如果饼干太多g<s，则for小孩遍历完就结束了。
可见，以小孩g为主要for遍历对象，饼干s只是通过index下标跟随，这是经典的手法，否则如果2层for就很不好了。
注意理解上述的点，因为一旦选择认定了小孩g无论如何都每次过1个，所以用for遍历，而饼干则随着小孩g遍历不一定
每次发得出去（比如遍历的小孩g[i]比当前最大饼干s[index]大时），因此作为if限定内的index--，这是常用的思路。

注：选定一方（小孩）for遍历i，另一方用index跟随，这是关键的思路。
注：这个index实际上相当精髓，好好理解，否则需要两重循环。
注：此题搭配图解理解更佳，P308。

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end()); // g为小孩
        sort(s.begin(), s.end()); // s为饼干
        int result = 0;
        int index = s.size() - 1;
        for (int i = g.size() - 1; i >= 0; i--) {
            if (index >= 0 && s[index] >= g[i]) {
                result++;
                index--;
            }
        }
        return result;
    }
};