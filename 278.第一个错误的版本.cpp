// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

核心思路：二分查找
比起常规的升序数组二分查找，此题更加容易，因为只有[f,f,f,f,t,t,t...] false和true两种，然后正常写二分查找的模板套路即可
[注] 经过推理，最后的mid计算出来，要么会在相邻f,t的f上，要么在相邻f,t的t上，所以要考虑两种情况，这两种情况都是可能发生的

class Solution {
public:
    int firstBadVersion(int n) {
        if (n == 0) return 0;
        long left = 1, mid = 0, right = n;
        while (left <= right) {
            mid = (left + right) / 2;
            if (isBadVersion(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;                
            }
        }
        return isBadVersion(mid) ? mid : mid + 1;
    }
};