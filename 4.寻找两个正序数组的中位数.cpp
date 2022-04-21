双指针，合并2个升序数组
困难题，应该用O(log(m+n))，但用了O(m+n)，所以并没满足要求，仅仅是为了熟悉了两个升序数组的合并merge过程

for循环里面是精髓，双指针i,j分别定位2个数组的进度，for条件为大的数组遍历完结束，即i < s1 || j < s2
然后是2个if，主要是为了区分merge数组该push哪一边，这里的逻辑稍微绕一点

以第1个if进行推导：（感觉应该不需要这么复杂，这里写的应该有冗余，后续遇到其他题思考精简的办法，或者参考其他人O(m+n)的解答）
第1层：nums1[i] <= nums2[j]，则push小的nums1[i]，反之push nums1[j]
第2层：i<s1，这个条件应该写在前面，因为你上述第1层的判断，应当满足i不能达到s1，（虽j也不能达到s2，但前面j==s2可以限制住不访问到后面）
第3层：j==s2，一旦j遍历完了，就无条件push nums1[i]（其实有条件，继续看第4层）
第4层：i!=s1，还有个条件，j遍历完了，但i不能遍历完，此时才可以无条件push nums1[i]

[注] 最后的doule不要遗忘，取在该取的位置；奇数偶数的计算，自己写2个例子就清楚了，比如merge分别为[1,2,3]和[1,2,3,4]

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int s1 = nums1.size(), s2 = nums2.size();
        vector<int> merge;
        for (int i = 0, j = 0; i < s1 || j < s2;) {
            if ((j == s2 && i != s1) || (i < s1 && nums1[i] <= nums2[j])) {
                merge.push_back(nums1[i]);
                i++;
            }
            if ((i == s1 && j != s2) || (j < s2 && nums1[i] > nums2[j])) {
                merge.push_back(nums2[j]);
                j++;
            }
        }
        int sm = merge.size();
        return sm % 2 ? merge.at(sm / 2) : (double)((merge.at(sm / 2 - 1) + merge.at(sm / 2)) / 2.0);
    }
};