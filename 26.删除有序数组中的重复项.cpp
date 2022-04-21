我的错误思路
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        int i = 1, k = 0;
        while (i < nums.size()) {
            while (i < nums.size() && nums[i - 1] == nums[i]) {i++;}
            nums[k] = nums[i - 1];
            i++;
            if (!(i >= nums.size() && nums[i-1] == nums[i-2])) k++;
        }
        if (nums[i-1] != nums[i-2]) nums[k] = nums[i - 1];
        return k + 1;
    }
};


举例：[1,1,2,2,3] [1,1,2,2,3,3]
核心：快慢双指针，fast用来定位下一个不一样的数，slow用来定位新的不重复数组下标。

思维误区1：因为第0数始终不会删，从第1个开始删除，所以fast和slow都从1开始，而我上面的解答为了从0开始，就取nums[k] = nums[i - 1]，
陷入误区，导致后面容易越界，所以要多思考简单直接的方法nums[slow] = nums[fast]，特殊的（比如从1开始）就特殊处理。

思维误区2：我上面的解答用了2个while，一看就不合理。“一般快慢双指针，就是1个while快的fast一直走，慢的slow看条件走，就比较合理，应该形成框架意识形态”。
这样边界条件fast>=n时就很直观简单，不需要过多考虑。因为fast的值在他第一次触及到（比如最后的3）时就已经赋过了。


所以此题的正确反推思路：先定快慢双指针框架，1个while1个快走1个慢走，然后nums[slow] = nums[fast]要确定，就会定nums[fast] != nums[fast - 1]，
为了不越界，一般都是i-1和i的形式，然后就会发现第0个数没给到slow，然后单独处理第0个数（此题刚好第0个数不需要处理）

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        int fast = 1, slow = 1; // wyh 都从1开始
        while (fast < n) {
            if (nums[fast] != nums[fast - 1]) {
                nums[slow] = nums[fast];
                ++slow;
            }
            ++fast; // wyh fast放在while最后++
        }
        return slow;
    }
};
