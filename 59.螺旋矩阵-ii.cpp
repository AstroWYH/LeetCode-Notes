数组 循环

思路：这类题很考验基础，没有特别的算法。画出3*3图形，遵循“左闭右开”从一而终的原则，方能统计不出错。

注：此题有几个点需要想到：1）要想到loop，需要不断loop来求解；2）n为奇数和偶数时遍历不同，
奇数遍历完后还剩个mid，偶数时直接遍历结束；）要想到坐标的思路，start_x、start_y作为每圈loop的起始坐标。
i、j作为每圈loop固定时，逐步顺时针去遍历整个圈的坐标，先动j++再动i++再动j--再动i--；3）只有用坐标的
方式遍历，才会4个for()里面一模一样的代码，count++即可，逐步累加反而是题最初的本意；4）offset很有意思，
每次进入下一个loop时，实际上start_x或start_y会往右下走一步，但是offset会由于两边的原因缩短2，因此，
理解(如第一个for条件)的j < start_y + n - offset很重要，可以自己画5*5在loop后变成3*3思考，
start_y+1但offset-2，最终的(start_y + n - offset)就缩小1，其实就是每次进入下一个loop，因为正方形
长度变为n-2了，所以i和j的遍历范围就会缩小1（从绝对坐标的角度，否则应该是缩小2），所以找规律得到公式：
(start_y + n - offset)，当然实际应该是推导得出的。

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int loop = n / 2;
        int mid = n / 2;
        int start_x = 0, start_y = 0;
        int count = 1;
        int offset = 1;
        int i = 0, j = 0;
        while (loop--) {
            i = start_x;
            j = start_y;

            for (j = start_y; j < start_y + n - offset; j++) {
                res[i][j] = count++;
            }
            for (i = start_x; i < start_x + n - offset; i++) {
                res[i][j] = count++;
            }
            for (; j > start_y; j--) {
                res[i][j] = count++;
            }
            for (; i > start_x; i--) {
                res[i][j] = count++;
            }

            start_x++;
            start_y++;
            offset+=2;
        }
        if (n % 2) {
            res[mid][mid] = count;
        }
        return res;
    }
};