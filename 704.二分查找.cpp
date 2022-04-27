二分查找

https://www.bilibili.com/video/BV1LJ411X76n?spm_id_from=333.337.search-card.all.click
b站的教学如上，没想到这个题上来就直接做对了。
https://blog.csdn.net/ShelleyLittlehero/article/details/80739884
二分查找的时间复杂度O(logn)

二分查找思想：
对于升序数组，设left为左，right为右，mid为(left + right) / 2（偶数刚好/2，奇数/2舍去小数，mid偏左一点不影响），
对比target和mid大小，如果target小了，则说明在（left, mid）左半区，因此另right = mid - 1（为啥-1，这就是算法规定的巧妙之处了，记住即可）
反之target大了，则说明在（right, mid）的右半区，应另left = mid + 1。三种情况写3个判断（if - else if - else）

考虑最后的特殊情况（left和right相邻（要么在没相邻的时候就找到了），left在right左边，left+1=right）：
情况1：target = nums[left]，那么mid = (left+right)/2 = left，答案直接就找到了。

情况2：target = nums[right]，那么mid = (left+right)/2 = left，target > nums[mid]，说明需要left = mid+1，
此时left=right，然后再计算就会得到mid=left=right，然后target=nums[mid]，答案就找到了。

情况3：nums[left]<target<nums[right]，target不存在，大小刚好在left和right中间，那么此时依然mid=(left+right)/2=left，
target>nums[mid]，所以left=mid+1=right，然后再计算mid=left=right，target<nums[mid]，此时right=mid-1，跟最早比起来，
变成了left和right的位置互换了，left和right相邻，但right+1=left的位置关系，此时再while (left <= right)就会不满足，
所以寻找结束，答案为不存在。

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, mid = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            mid = (left + right) / 2;
            if (target == nums[mid]) { // wyh [注]比大小target写在左边，更容易思考
                return mid;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};