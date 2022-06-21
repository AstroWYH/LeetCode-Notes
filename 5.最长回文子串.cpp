中心扩散法 动态规划

思路：此题适合中心扩散法，但中心扩散法不是通用算法，因此简述思路。
for()遍历字符串s，对每一个字母i，都考虑从自身中心往左右扩散(抽出函数)，如果左右一样则继续扩散，
否则返回并记录当前回文字符串[l,r]坐标。整个遍历完成后，取最长ans即可。时间复杂度O(n²)。

注：可从自身i左右扩散，也可从i,i+1左右扩散(因为回文字串有奇偶长度2种)，因此有2种情况。
注：记录当前i返回的长度时，end-start只需要考虑max(odd,even)情况即可。
注：pair<int,int>返回用auto [l,r] = ...，中括号接住。

class Solution {
public:
    pair<int, int> expandAroundCenter(string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return {left + 1, right - 1};
    }
    string longestPalindrome(string s) {
        if (s.length() < 2) return s;
        int start = 0, end = 0;
        for (int i = 0; i < s.length(); i++) {
            auto [left_odd, right_odd] = expandAroundCenter(s, i, i);
            auto [left_even, right_even] = expandAroundCenter(s, i, i + 1);
            if (right_odd - left_odd > end - start) {
                start = left_odd;
                end = right_odd;
            }
            if (right_even - left_even > end - start) {
                start = left_even;
                end = right_even;
            }
        }
        return s.substr(start, end - start + 1);
    }
};

思路：动态规划解法，回文子串bab和cbabc之间存在关联，如同n和n-1类似，因此存在状态转移关系，可采用动归解法。
参考视频题解：https://leetcode.cn/problems/longest-palindromic-substring/solution/zui-chang-hui-wen-zi-chuan-by-leetcode-solution/

注：此题的动归解法，可以理解，但不易想到，以下为大致思路。
注：dp[][]数组是开始就开辟，空间复杂度O(n²)，在动归过程递推中，会逐渐去填充dp[i][j]的值，每轮for()
填一个，递推中最新的一个[i,j]位置处的dp[i,j]。
注：实际上相比中心扩散法有不少浪费。时间复杂度O(n²)，动归主要是空间换时间。

动归五部曲：
1：确定dp数组及下标的含义。dp[i][j]表示s[i..j]是否是回文串。vector<vector<int>> dp(n,vector<int>(n))。
2：确定递推公式。dp[i][j]=(s[i]==s[j])&&(dp[i+1][j-1])。实际情况可以写成if-else分开写。
例如：
                if (s[i] != s[j]) { // wyh
                    dp[i][j] = false;
                } else {
                    if (j - i < 3) {
                        dp[i][j] = true;
                    } else { // wyh
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
3：初始化dp数组。所有长度为1的子串都是回文子串：dp[i][i]=true。
4：...
5：...