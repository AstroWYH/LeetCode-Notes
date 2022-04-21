双指针沾边

核心思想
一般情况：
对每1个house（i），heater要么选它自己前面1个，要么是后面1个，选离得近的为d
对于遍历所有的房子,选所有d里面最远的
特殊情况：
对于第1个heater在最左边，所有的i都只有1个d
对于最后1个heater在最右边，所有的i都只有1个d
思考: 
1）核心思想为转变思维，不要盯着每个heater,要盯着每个house，每个house要么前面一个要么后面一个；转换思维后，[注]的边界问题自然就消失了
2）此题双指针在于i, j的运用, 与其他不同，i是遍历houses，而j是快速定位i左右最近的heater，后面j又可以单独作为判断条件当主角，需要理解这种i, j独立运转的模式
3）实际上还是3段分，左边的i，中间的i，右边的i，各自不同的处理情况

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end()); // wyh 先对两个数组进行排序, 方便后续计算
        int i = 0, j = 0, ans = 0; // wyh i遍历houses
        int d = INT_MAX;
        for (; i < houses.size(); i++) {
            while (j < heaters.size() && heaters[j] < houses[i]) { // wyh j快速定位到house[i]左右最近的heater, 分别为(j-1, j)
                j++; // wyh [注]如果第1个heater在house左边, 或最后1个heater在house右边, 则也符合上述情况, 正常计算即可
            }
            if (j == 0) { // wyh 如果上述定位失败, 说明上来j就在i右侧, 则只有1个d
                d = heaters[0] - houses[i];
            } else if (j == heaters.size()) { // wyh 如果j已经定位到heaters最右, 则只有1个d
                d = houses[i] - heaters[j - 1];
            } else { // wyh 一般情况, 找到i左右heater最近的
                d = min(houses[i] - heaters[j - 1], heaters[j] - houses[i]);
            }
            ans = ans < d ? d : ans; // wyh 在遍历i的过程中, 有较大的d就进行替换
        }
        return ans; 
    }
};
/*
@可爱抱抱呀
执行用时：7 ms, 在所有 Java 提交中击败了100.00%的用户
内存消耗：41.7 MB, 在所有 Java 提交中击败了43.59%的用户
2021年12月19日 13:42
*/
讨论区中看到的一句话精华：对于每个房屋，要么用前面的暖气，要么用后面的，二者取近的，得到距离
class Solution {
    public int findRadius(int[] houses, int[] heaters) {
        int ans=0;
        int d=(int)2e9;
        Arrays.sort(houses);
        Arrays.sort(heaters);
        int j=0;
        for(int i=0;i<houses.length;i++){
            while(j<heaters.length&&heaters[j]<houses[i]){j++;}
            if(j==0){d=heaters[0]-houses[i];}
            else if(j==heaters.length){d=houses[i]-heaters[j-1];}
            else{d=Math.min(heaters[j]-houses[i],houses[i]-heaters[j-1]);}
            ans=Math.max(ans,d);
        }
        return ans;
    }
}

