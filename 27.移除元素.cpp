数组 快慢双指针

思路：画出数组的图，经典的O(1)数组后面覆盖前面，考虑快慢双指针，遍历fast如果正常情况就赋值给slow，
如果遇到val需要删除，就此次不赋值个slow。

注：此题容易想到erase()，但由于erase()后迭代器失效变成野指针，就很麻烦且容易出错，题型考点本意也不是erase()。
对于数组O(1)的原地替换，要想到可以用前面覆盖后面，所以可以考虑快慢双指针，fast逐个遍历原数组，
当for(fast)遍历过程遇到需要删除的数据时，就if(slow)进行处理，最终slow记录新数组下标。
注：注意画图理清思路。数组，slow，fast。

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0, fast = 0;
        for (; fast < nums.size(); fast++) {
            if (nums[fast] != val) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};