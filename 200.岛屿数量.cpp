深度优先搜索 DFS 递归 广度优先搜索 BFS 队列

DFS解法：

思路：DFS、BFS的经典例题，和二叉树的遍历“DFS、BFS”相似，是升级版的二叉树，简化版的图。
两层for()遍历每个坐标(x,y)，对每个坐标执行DFS()，并记录已遍历过的坐标“记为0，避免循环重复遍历”。
在两层for()中完成一次完整的递归(不管递归了几层)，就算一个岛屿(cnt++)。

{
    以二叉树前序遍历的DFS为例：
    void traverse(TreeNode* cur, vector<int>& vec) {
        if (cur == nullptr) return;
        vec.push_back(cur->val);
        traverse(cur->left, vec);
        traverse(cur->right, vec);
    }
    递归三部曲：
    1）递归函数参数、返回值。此题不需要返回值，为void；参数为当前节点指针*cur，和统计结果的vec。
    2）递归终止条件。此题为cur==nullptr，遍历到叶子节点后，再往下一层，cur就会为空（没有节点了）。
    3）递归函数内逻辑。此题根据二叉树遍历方式（前、中、后序），来决定push(cur)、traverse(left)、
    traverse(right)的执行顺序，此题是中-左-右。
}

类似的，本题DFS的递归三部曲：
1）递归函数参数、返回值。无需返回值，参数为两层for()来遍历每个位置的坐标(x,y)。
2）递归终止条件。A：超出网格边界终止，类似二叉树访问到node(nullptr)终止，先访问到后return，
即“先污染后治理”。B：走到标记置0的坐标，也需要return，因为已经走过了，否则一直DFS循环遍历出不来。
3）递归函数内逻辑。A：类似二叉树“递归遍历其左右2个子树”，岛屿DFS也需要“递归遍历其上下左右4个坐标”，
一直往深处走，“只要你又连了东西，那我就一定会走到”，直到走到递归出口“没连东西了”为止，这也是DFS的含义。
B：不同于二叉树的地方，为避免循环重复DFS(leetcode题解有GIF)，遍历的坐标需要标记(置0)。

注：岛屿问题的DFS，类似二叉树遍历DFS，应当作为模板记住。

class Solution {
public:
    void dfs(int x, int y, vector<vector<char>>& grid) {
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) return;
        if (grid[x][y] == '0') return;

        grid[x][y] = '0'; // 岛屿网格问题的特殊处，遍历过后记0

        dfs(x + 1, y, grid);
        dfs(x, y + 1, grid);
        dfs(x - 1, y, grid);
        dfs(x, y - 1, grid);
    }

    int numIslands(vector<vector<char>>& grid) {
        int cnt = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') { // DFS、BFS若想cnt++，这是必须条件，表示遇到了新的某片岛屿
                    dfs(i, j, grid);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

BFS解法：

思路：和“二叉树的层序遍历-BFS-队列”相似，用队列que的方式。仍然两层for()遍历每个坐标(x,y)，遍历过程中，
如果遇到岛屿“1”，则将其push进que，否则跳过遍历下一坐标。对push进que后的node，首先会被pop得到node，
然后检查其“上下左右”是否仍为岛屿，如果pop出来的node的“上下左右”仍有岛屿(为1)，则又排队push进que，并记录置0。
然后while()重复检查que，直到que清空，表面某片岛屿已清理干净。

注：和“二叉树的层序遍历-BFS-队列”几乎思路一样，注意几个关键点：
1）：队列que首先“在while()之前”拿来存当前遍历满足条件的node，如“岛屿、root”。然后会“while()循环存放”
“刚才node”“紧连的满足条件的node”。然后while()过程中que中的node总会pop()出来，对齐“紧连node”进行上述判断。
2）：某片岛屿“一片连接的1”遍历过程中：
BFS：仅仅会检查“当前node”的“上下左右紧连”，而后续“是否存在一片连接的1的情况，
会由que中源源不断的node来解决，每个node只pop出来检查“当前node”的“上下左右紧连”，满足条件则push进que，并置0。
DFS：会从“当前node”检查“上下左右挨个遍历，并一路到底”，一层递归dfs()函数检查一层紧连。
3）：某片岛屿的遍历过程while(que.empty())为空结束，整个过程则是两层for()走完结束。

注：某片岛屿 = 二叉树。
注：岛屿和二叉树也有不同处，二叉树while()内有个for()，实际上更稍不好理解一点，画图理解即可。
注：这类队列问题，核心是把握while()每层做的事，和que()什么时候pop()当前node用来“检查紧连”，什么时候push()
“紧连满足条件的node”，然后“处理当前node->处理当前node紧连满足条件的node”，就是进入了下一个while()。

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int cnt = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == '1') { // DFS、BFS若想cnt++，这是必须条件，表示遇到了新的某片岛屿
                    cnt++;
                    grid[i][j] = '0'; // 岛屿网格问题的特殊处，遍历过后记0
                    queue<pair<int, int>> que;
                    que.push({i, j});
                    while (!que.empty()) {
                        auto node = que.front();
                        que.pop();
                        int x = node.first, y = node.second;
                        if (x - 1 >= 0 && grid[x - 1][y] == '1') { // 判断左点是否满足岛屿
                            que.push({x - 1, y});
                            grid[x - 1][y] = '0';
                        }
                        if (x + 1 < grid.size() && grid[x + 1][y] == '1') {
                            que.push({x + 1, y});
                            grid[x + 1][y] = '0';
                        }
                        if (y - 1 >= 0 && grid[x][y-1] == '1') {
                            que.push({x, y - 1});
                            grid[x][y - 1] = '0';
                        }
                        if (y + 1 < grid[0].size() && grid[x][y + 1] == '1') {
                            que.push({x, y + 1});
                            grid[x][y + 1] = '0';
                        }
                    }
                }
            }
        }

        return cnt;
    }
};

{
    以二叉树的层序遍历为例：
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

    第一层while()：que中，处理第一层node(即root)，第一层node(即root)出去，第二层2个node进que。
    第二层while()：que中，处理第二层2个node，第二层2个node出去，第3层4个node进que。其中for()内分2段。
    ...

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
}
