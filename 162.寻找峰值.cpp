二分法 二分查找

思路：此题在于要想到，当随机落到点i时，可能处于上坡、下坡、坡峰、坡谷，由于题干是“任意找峰值”，
因此坡谷可以不考虑，因为向左向右爬坡都一样。然后就是判断出当前的位置，向左或向右爬坡，如果是坡峰返回。

注：此题二分法可以解决，二分的关键仍在于“对mid、target的判断”。
注：target就是坡峰，如果mid处于上坡，则说明坡峰在右侧，则left=mid+1。反之，如果mid处于下坡，
则说明坡峰在左侧，则right=mid-1。
注：不断控制l、r缩小范围找target坡峰，和“升序数组中，二分法借助mid寻值target类似”。
注：题干提到O(logn)，虽然此题不是升序数组，但仍应该想到“二分法”。

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size() < 2) return 0;
        if (nums.size() == 2) return nums[0] > nums[1] ? 0 : 1;
        if (nums[0] > nums[1]) return 0; // 这4个if均为边界条件
        if (nums[nums.size() - 1] > nums[nums.size() - 2]) return nums.size() - 1;
        int left = 1, right = nums.size() - 2;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1]) {
                return mid;
            }
            if (nums[mid - 1] < nums[mid]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return 0;
    }
};