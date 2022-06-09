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

二叉树 广度优先搜索 BFS 层序遍历 队列

思路：此题官方题解是想考察“层序遍历+双端队列+广度优先搜索”，和“102.二叉树的层序遍历”相似，
区别在于每层需要颠倒顺序。自己解法的思路为，在que的基础上新增reque，que正常遍历，deque则
每层反过来遍历，然后用layer判断在不同奇偶层时，vec收集对应每层的node即可。

注：此解法虽能通过，但并不优秀。一是增加了空间复杂度reque，二是题意想考察的是双端队列。
注：此题是“二叉树层序遍历”的变化，层序遍历的模板要记住并理解，也是理解队列的典型题。

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) return result;
        queue<TreeNode*> que;
        queue<TreeNode*> reque;
        que.push(root);
        reque.push(root);
        int layer = 0;
        while (!que.empty()) {
            vector<int> vec;
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node_que = que.front();;
                TreeNode* node_reque = reque.front();;
                if (layer % 2 == 0) {
                    vec.push_back(node_que->val);
                } else {
                    vec.push_back(node_reque->val);
                }
                que.pop();
                reque.pop();
                if (node_que->left) que.push(node_que->left);
                if (node_que->right) que.push(node_que->right);
                if (node_reque->right) reque.push(node_reque->right);
                if (node_reque->left) reque.push(node_reque->left);
            }
            ++layer;
            result.push_back(vec);
        }
        return result;
    }
};

LeetCode官方题解

二叉树 广度优先搜索 BFS 层序遍历 双端队列

思路：官方题解和“102.二叉树的层序遍历”更相似了，原来“双端队列”并不体现在que上，二是体现在之前
收集每层的node上。整个层序遍历的思路没变，仅仅是收集的过程从vec->deque。

注：官方题解用isOrderLeft表示每层的反转，自己用的layer，其实都可以，但isOrderLeft是值得学习的方式。
注：收集过程的vec->deque并不容易想到，这里可以学习到deque的性质。deque的push_back()其实和vec一样，
而push_front()从前端插入就是有趣的点了，可以实现“颠倒”。
注：可见，官方题解和代码随想录的“二叉树层序遍历+广度优先搜索+队列”的模板是相同的，应该理解好并记住。

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) return result;
        queue<TreeNode*> que;
        que.push(root);
        bool isOrderLeft = true;

        while (!que.empty()) {
            deque<int> levelList;
            int size = que.size();
            for (int i = 0; i < size; ++i) {
                auto node = que.front();
                que.pop();
                if (isOrderLeft) {
                    levelList.push_back(node->val);
                } else {
                    levelList.push_front(node->val);
                }
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.emplace_back(vector<int>{levelList.begin(), levelList.end()});
            isOrderLeft = !isOrderLeft;
        }

        return result;
    }
};

