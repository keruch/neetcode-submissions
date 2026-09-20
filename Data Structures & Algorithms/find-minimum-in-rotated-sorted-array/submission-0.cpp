class Solution {
public:
    int findMin(vector<int> &nums) {
        int l = 0, r = nums.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            // searching for the first element <= the last
            if (nums[m] <= nums.back()) r = m;
            else l = m + 1;
        }

        // no ub: since our P uses <= n.back(),
        // we always point to some existing element 
        return nums[l];
    }
};
