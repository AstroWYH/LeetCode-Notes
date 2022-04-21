算法：二叉搜索树、动态规划（领悟思想，暂不会做）

思路：
1）遍历根节点为1~n，每种根节点的情况加起来
2）在遍历第i个节点时，i的左右分别有各自的长度1~i-1和i+1~n，又递归式的遍历，直到递归遍历到最底端为止

动态规划：根据题目自行建模类似递归的数学公式，可以根据举例来得出公式，类似G(n)=G(0)...G(n-1)之类的，然后写程序
G(n)为节点长度为n的二叉搜索树个数，也是本题寻求的return
F(i,n)为节点长度为n，但根节点为i时的二叉搜索树个数
公式不便写，题解为：https://leetcode-cn.com/problems/unique-binary-search-trees/solution/bu-tong-de-er-cha-sou-suo-shu-by-leetcode-solution/

// wyh 这一步没看懂，属实有点尴尬，注意配合官方题解看
// wyh 意会到了，其实就是累加的意思，注意2个循环即可，i动态取代了n，j取代了i，每个j加完后累加到G[i]上，就是求和公式的逐步体现
// wyh j<=i是理所应当，因为i代表此时的n，当前n就i这么大，j自然不能超过n
// wyh i逐渐增加到n的过程中，G[]是每1个i对应1个G[i]，所以每个G[i]独立计算，只不过要通过多次计算得到（因为遍历j实现累加）
// wyh 当i逐渐增大，j的最大值(就是i)也会逐渐增大，也就体现了G[n]=G[n-1]...G[0]这一思想

class Solution {
public:
    int numTrees(int n) {
        vector<int> G(n + 1, 0); // wyh n=3时，G[]开始为{0,0,0,0}，最后为G: {1, 1, 2, 5}
        G[0] = 1;
        G[1] = 1;

        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                G[i] += G[j - 1] * G[i - j];
            }
        }
        return G[n];
    }
};
