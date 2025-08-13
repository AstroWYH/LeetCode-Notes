/*
 * @lc app=leetcode.cn id=54 lang=cpp
 * @lcpr version=30204
 *
 * [54] 螺旋矩阵
 */


// @lcpr-template-start
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 装结果的res。
        vector<int> res;

        // 初始化上界u、下界d、左界l、右界r。
        int u = 0;
        int d = matrix.size() - 1;
        int l = 0;
        int r = matrix[0].size() - 1;

        // 进入循环
        while (true) {
            // 基于左上角，从左往右遍历，依次res装入遍历结果。
            for (int i = l; i <= r; i++) res.push_back(matrix[u][i]);
            // 遍历完成后，上界u++，如果已经大于下界d，则跳出循环，表明全部处理完成。
            // 极限条件是，此时还剩一行，u=d，从左往右遍历完后，u>d，跳出循环，全部处理完成。
            if (++u > d) break;
            // 基于右上角，从上往下遍历，依次res装入遍历结果。
            for (int i = u; i <= d; i++) res.push_back(matrix[i][r]);
            // 遍历完成后，右界r--，如果已经小于左界l，则跳出循环，表明全部处理完成，同上，下面也类似。
            if (--r < l) break;
            for (int i = r; i >= l; i--) res.push_back(matrix[d][i]);
            if (--d < u) break;
            for (int i = d; i >=u; i--) res.push_back(matrix[i][l]);
            if (++l > r) break;
        }

        return res;
    }
};

// @lc code=end



/*
// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3,4],[5,6,7,8],[9,10,11,12]]\n
// @lcpr case=end

 */

