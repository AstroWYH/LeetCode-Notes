回溯+组合+代码随想录

思路：没想到直接做对了，在77-组合的基础上稍加变化，多了一个判断条件sum，整体还是代码随想录回溯的思想。
1）确定纵轴长度为k。
2）确定横轴小for长度为9。
3）确定结束条件为com.size() == k，同时当sum == n时摘果子。

代码注释：
1、2：sum跟着push和pop走。
3：可剪枝，com.size() == k时结束，但有时候甚至不需要到k，比如[1,2,4]=8，那么当遍历[1,7]直接为8的时候，
后面就可直接剪枝了。
4：可剪枝，i <= 9经典小for剪枝。

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtrack(k, n, 1);
        return coms;
    }
private:
    void backtrack(int k, int n, int idx) {
        if (com.size() == k) { // wyh 3
            if (sum == n) {
                coms.push_back(com);
            }
            return;
        }
        for (int i = idx; i <= 9; i++) { // wyh 4
            com.push_back(i);
            sum += i; // wyh 1
            backtrack(k, n, i + 1);
            com.pop_back();
            sum -= i; // wyh 2
        }
    }
    vector<vector<int>> coms;
    vector<int> com;
    int sum = 0;
};