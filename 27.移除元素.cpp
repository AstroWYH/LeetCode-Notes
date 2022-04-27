class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        for (auto it = nums.begin(); it != nums.end(); it++) {
            if (*it == val) {
                // nums.erase(it);
                // it = nums.begin();
                nums.insert(it, it++, nums.end());
            }
        }
        return nums.size();
    }
};