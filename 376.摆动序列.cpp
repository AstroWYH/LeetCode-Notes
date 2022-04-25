贪心算法

思路：核心是找到prediff和curdiff，每次遍历i过程中，这两个数需要一正一负或一负一正，符号相反，
此为局部最优，如果上述条件成立则result++，不断累加。

注：如[2,3]时，遍历没有prediff只有curdiff，因此将其看作[2,2,3]，意思其实是让prediff=0可以通过，
就是刚开始的时候需要注意。此外，这个题解配合prediff=curdiff赋值的位置，刚好解决了中间两数相等的问题，
如[2,5,3,3,4]，中间两个3，如果每次遍历i都prediff=curdiff赋值，则条件prediff=0时会出问题，因为
遍历到“平”的时候（curdiff=0不会进prediff=0会进）就进入了if，实际是不能进入的。
注：此题搭配图解看理解更佳，P310。

1：题干表示，少于2个元素为摆动序列
2：size=2个元素起步，result从1开始算，如果只2个元素，则[2,3]会进if返回2，[2,2]不会进if返回1
3：i和i+1遍历，注意i<size-1，不是平时的i<size

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size(); // wyh 1
        int curdiff = 0, prediff = 0;
        int result = 1; // wyh 2
        for (int i = 0; i < nums.size() - 1; i++) { // wyh 3
            curdiff = nums[i + 1] - nums[i];
            if ((curdiff > 0 && prediff <= 0) || (curdiff < 0 && prediff >= 0)) {
                result++;
                prediff = curdiff;
            }
        }
        return result;
    }
};