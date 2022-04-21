滑动窗口，字符串

核心思想：滑动窗口错车。nums1和nums2两个字符串，虽然不是谁是谁的字串关系，但是也滑动窗口，滑就完事了。

第1轮for：先固定nums1，遍历nums1，拿nums2的首字母从nums1的首，挨个对齐往后滑，直到nums2的首对齐nums1的尾，
反过来也一样，遍历nums2，挨个拿nums1去对齐滑动。这是2个单独的for循环，复杂度分别为o(n1)和o(n2)。

举例1：
  i=1
4 1 2 3
  3 1 2 5 6
  j=0
举例2：
  i=1
4 1 2 3
  3 1
    j=1

第2轮for：对每1次错车情况，单独用j来开启新的遍历（[注]：之前想i来继续第2轮for，后来发现很多问题。这种情况直接用j，
因为是相对位置关系直接j=0开始，省事。以j开始，何时结束？考虑例1，应该遍历完n1结束，即j+i<n1；考虑例2，应该遍历完n2结束，
即j<n2。
第2轮for内具体：遍历j过程中，如果nums1[j + i] == nums2[j]，则累计k++，遇到非连续情况又k=0，期间更新ans为最大k。


class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if (n1 == 0 || n2 == 0) return 0;
        int ans = 0;
        for (int i = 0; i < n1; i++) {
            int k = 0;
            for (int j = 0; j + i < n1 && j < n2; j++) {
                if (nums1[j + i] == nums2[j]) {
                    k++;
                    ans = max(k, ans);
                } else {
                    k = 0;
                }
            }
            ans = max(k, ans);
        }
        /* ------------------------------- */
        for (int i = 0; i < n2; i++) {
            int k = 0;
            for (int j = 0; j + i < n2 && j < n1; j++) {
                if (nums2[j + i] == nums1[j]) {
                    k++;
                    ans = max(k, ans);
                } else {
                    k = 0;
                }
            }
            ans = max(k, ans);
        }
        return ans;
    }
};