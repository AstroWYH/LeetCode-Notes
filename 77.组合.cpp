回溯+组合+代码随想录

足够优秀的题解 from 代码随想录
https://github.com/youngyangyang04/leetcode-master/blob/master/problems/0077.%E7%BB%84%E5%90%88.md
还可以进一步优化剪枝

// 回溯经典模板
void backtracking(参数) {
    if (终止条件) {
        存放结果;
        return;
    }
    for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}

class Solution {
private:
    vector<int> com;
    vector<vector<int>> coms;
    void backtrack(int n, int k, int idx) {
        if (com.size() == k) {
            coms.push_back(com);
            return;
        }
        // for (int i = idx; i <= n; i++) {
        for (int i = idx; i <= n - (k - com.size()) + 1; i++) { // wyh 剪枝优化，理解后记住
            com.push_back(i);
            backtrack(n, k, i + 1);
            com.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        backtrack(n, k, 1);
        return coms;
    }
};