回溯 排列问题 递归

思路：此题属于n个数按一定规则排列，有几种排列方式。使用“回溯->排列”问题模板即可。

注：回溯问题中，“排列”和“组合”区别在于“排列有序，组合无序”。

注：回溯代码层面的逻辑区别(排列&组合)：
1）对于递归中的for()，排列每次从0开始遍历，组合每次从idx开始。因为组合问题中，随着递归(深度)的进行，
每次会“压缩选择范围”，排列则不会，所以每次从0开始。
2）排列需要用一个布尔数组used，来记录随着递归(深度)的进行，谁是已经使用的，谁还没使用。

注：排列的树，是一颗完整的树；组合的树，是一颗从左往右越来越稀疏的树。看代码随想录的图(直观)。

注：对于排列&组合的回溯问题，画图要点：
1）回溯的本质是暴力穷举，大多都是“在集合中递归查找子集”。
如果不用回溯(递归)解，那么可能需要很多次for()，代码是没法写的。
2）树的宽度是集合的大小，树的深度是递归的次数。for()是每层的横向遍历，递归是纵向遍历。
3）画图时，往往可以将第一层(如本例，遍历1,2,3)的头上，总结成一个“虚拟头1234”，这样更好理解。
4）“组合的idx”和“排列的used”需要理解到位。
5）组合回溯的剪枝问题，可以作为补充掌握。

class Solution {
public:
    vector<vector<int>> coms; // 这两个使用全局变量，可以让回溯函数的参数更少，看上去更简洁
    vector<int> com;
    void backtracking(vector<int>& nums, vector<bool>& used) {
        if (com.size() == nums.size()) {
            coms.push_back(com);
            return;
        }
        for (int i = 0; i < nums.size(); i++) { // 如果是组合问题，这里就要用idx来随着递归深入，压缩范围
            if (used[i] == true) continue; // 排列问题的used，好好理解
            used[i] = true;
            com.push_back(nums[i]);
            backtracking(nums, used);
            com.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return coms;
    }
};