class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;

        // always keep it half-bound, so we don't miss egde elements!
        // when r is exclusive [l; r), then
        // 1. r = m (vs. r = m-1 in [l; r])
        // 2. while l < r (vs. l <= r)
        // 3. r = n.size() (vs. r.size()-1)
        int l = 0, r = nums.size();

        while (l < r) {
            int m = l + (r - l) / 2; // avoid overflow
            if (nums[m] == target) {
                return m;
            }
            if (nums[m] < target) {
                l = m + 1;
            } else {
                r = m;
            }
        }

        return -1;
    }
};
