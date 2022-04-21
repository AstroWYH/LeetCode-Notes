回溯+组合+代码随想录

思路：这题居然做对了，依然是套用模板，画好树形图。
首先需要思考，最重要的就是确定纵轴和横轴的遍历方式。
1）确定纵轴遍历长度为k，即digits的长度，如手机号码"52"，则为2。因为这决定了coms最终装几个数，递归几次。
2）确定横轴遍历长度为vec_pair[level].second，即每层vec_pair中字符串的长度，
如第1层{'5', "jkl"}里的"jkl"为长度3，后面都不一样，因为这决定了横轴每层每次递归的小for的长度。
实际上来看，横轴的小for长度是for(i-n)是i和n共同来决定，要么像组合问题i累加，固定n；
要么像此题，i始终从开始出发，n长度则不固定，由vec_pair[level].second来决定。
3）确定结束条件为com.size() == k，因为一共就选出k个号码来。

代码注释：
1：这个char很关键，'a'就是char，"a"就是string，可以用typeid(x).name()打印看类型。
2：画出树形图，就理解为什么这里是level，具体看横轴每层的每个小for循环，到底需要按什么方式遍历，
这里显然遍历跟vec_pair每层装的内容有关。
之前的77-组合是idx，那是因为横轴每层每个的小for循环是从上层下来后依次递增的，如上层1，则下层234，
上层2，则下层34。
3：vector<pair<char, string>>是对map不熟悉的权宜之计，后续换map。但也有不错的方法和性质，
比如可以按顺序push，而且pair的访问也简单，如.first，没有map迭代器那么麻烦。
4：这个题的横轴长度是vec_pair[level].second的长度，n根本没用到。

class Solution {
private:
    vector<string> coms;
    string com;
    map<char, string> map_all = { // wyh 1
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"},
    };
    void backtrack(int n, int k, int level, vector<pair<char, string>> vec_pair) {
        if (com.size() == k) {
            coms.push_back(com);
            return;
        }
        for (auto s : vec_pair[level].second) { // wyh 2
            com.push_back(s);
            backtrack(n, k, level + 1, vec_pair);
            com.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        int k = digits.length();
        if (k == 0) return {};
        vector<pair<char, string>> vec_pair; // wyh 3

        for (int i = 0; i < k; i++) {
            vec_pair.push_back({digits[i], map_all.at(digits[i])});
        }
        int n = vec_pair[0].second.length();

        backtrack(n, k, 0, vec_pair); // wyh 4
        return coms;
    }
};