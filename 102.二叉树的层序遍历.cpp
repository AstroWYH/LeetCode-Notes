/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

二叉树 迭代 广度优先搜索 BFS 层序遍历 队列

思路：经典-二叉树层序遍历-迭代(BFS)解法。此题是广度优先搜索，即一层搜完了再进入下一层，这点上很容易理解。

注：此题为“二叉树-广度优先搜索”的模板，需要理解并记住用“队列”完成该“层序遍历”的方式。
注：画图理解队列的运作很重要，P154。

注：两层循环while()-for()。“每一层while()代表一个阶段”，每一阶段都将二叉树的这一层的“本阶段成果vec”“用result”记录下来。
即result.push_back(vec)。for()遍历“当前阶段的队列que”，遍历过程中将“本阶段队列que”中的“节点node们”依次剔除，
并依次存入“本阶段成果vec”中，然后再将“下一阶段的节点node们”“先左后右”地加入队列que，再等下一个阶段的while()循环使用。

注：vec<vec> result(int)用来记录总结果，其由“每一阶段的结果vec(int)组成”。que(node*)用来记录“每一阶段的node们”，
是动态变化的，如果“上阶段的node们被剔除，下阶段的node们就会进来”，在for()内完成。“que和vec存在先后关系”，
在当前阶段遍历node们时，总是先que推出node，然后vec去记录该node，然后que去记录该node的下一阶段node，这其实就是for()内逻辑。

还有一点注意，就是que此时去记录“当前node的下一阶段node们”时，一般“当前阶段的node们还没完全推出”，就会存在que内
“既有当前阶段又有下一阶段的node”，但这不影响，因为下一阶段的node们进来后，是排在que后面的，无所谓。
其实这也是for()在遍历过程中正常会出现的情况，一旦一个完整for()遍历完，即经过一个完整while()，上述情况就不存在了，
que内此时必然全装的是“干净的下一阶段的node们”了。

1：第一个node，即root*，是在while()外推入队列que的，这也体现了上述que的“领先”思想。
2：vec的初始化位置，是在while()内for()外，因为vec是记录每个完整for的阶段性成果的，即每个阶段的node们。
3：由于que在每次for()内动态变化，所以要在for外用“固定size”提前确定好“该阶段que的长度”。
4：for()内遍历中，注意要每次que推出首节点后，再用vec记录阶段node，que始终“领先”vec。

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) return result;
        queue<TreeNode*> que;
        que.push(root); // wyh 1
        while (!que.empty()) {
            vector<int> vec; // wyh 2
            int size = que.size(); // wyh 3
            for (int i = 0; i < size; i++) {
                auto node = que.front();
                que.pop(); // wyh 4
                vec.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right); 
            }
            result.push_back(vec);
        }
        return result;
    }
};