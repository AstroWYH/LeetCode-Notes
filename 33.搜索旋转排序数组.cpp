二分法 二分查找

思路：不仅仅是整段升序数组可以二分法，分开的两段升序数组也可以二分法。
将数组从mid一分为二，其中一定有一段是有序的，另一段可能是有序，也大概率是部分有序(即还是两段有序)。
此时有序部分用二分法查找。无序部分再一分为二，其中一段一定有序，另一段可能有序，大概率是部分有序。如此循环。
比如：
例1：5 6 0 1 2 3 4  nums[mid]为1，则mid左半边无序，右半边有序
例2：5 6 7 8 9 1 2 nums[mid]为8，则mid左半边有序，右半边无序
虽思路如此，但整体操作起来统一用二分法处理就行，无论对于有序一边还是无序一边，都只需要继续进行二分法。
如例1，若target在无序左边，则right=mid-1；若在有序右边，则left=mid+1。反之，例2同理。

注：看到“有序数组”要想到“二分法”。
注：看到“O(logn)”复杂度要想到“二分法”。
注：二分法应作为模板记住：
1）nums边界条件判断。
2）左右指针赋初值，left=0,right=nums.size()-1。
3）while(left<=right)循环条件，左指针最多与右指针重叠，不能越过。
4）while()内mid指针赋值，mid=(left+right)/2。mid指针为左右指针的中间值，向下取整。
5）判断满足条件，if(target==nums[mid]) return mid。判断其他条件，并根据情况移动left、right左右指针。
移动过程中，left=mid+1，right=mid-1，左右指针一般都是基于mid指针移动一位，“左移中右，右移中左”。
6）return -1。表示while()二分法的循环过程中，最终没找到符合条件的值。

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0) return -1;
        if (nums.size() == 1) return nums[0] == target ? 0 : -1;
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (target == nums[mid]) return mid;
            if (nums[0] <= nums[mid]) { // 说明左半边此时是升序数组，右边不是
                if (nums[0] <= target && target < nums[mid]) { // 说明target在升序数组内
                    right = mid - 1;
                } else { // 说明target不在升序数组内
                    left = mid + 1;
                }
            } else { // 此时右边是升序数组，左边不是
                if (nums[mid] < target && target <= nums[nums.size() - 1]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};

class Solution {
public:
    int search(vector<int>& nums, int target) {
      if (nums.size() == 0) return -1;
      if (nums.size() == 1) return nums[0] == target ? 0 : -1;
      int mid = 0;
      int left = 0, right = nums.size() - 1;
      while (left <= right) {
        mid = (left + right) / 2;
        if (nums[mid] == target) {
          return mid;
        }
        if (nums[mid] >= nums[left]) { // 这里边界判断改为nums[left]，更容易理解
          if (nums[left] <= target && target < nums[mid]) { // 这里边界判断改为nums[left]，更容易理解
            right = mid - 1;
          } else {
            left = mid + 1;
          }
        } else {
          if (nums[mid] < target && target <= nums[right]) { // 这里边界判断改为nums[right]，更容易理解
            left = mid + 1;
          } else {
            right = mid - 1;
          }
        }
      }
      return -1;
    }
};
