#include<ranges>

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int m = 0;
        unordered_set<int> nums_hs(nums.begin(), nums.end());

        // nums_hs served as dedup, so no need to keep
        // track of viewed elements
        for (int n : nums_hs) {
            if (!nums_hs.contains(n-1)) {
                m = max(m, view(n, nums_hs));
            }
        }

        return m;
    }

    // contract: `nums` always contains `n`
    int view(int n, const unordered_set<int>& nums) {
        int seen = 1;
        while (nums.contains(n+seen)) {
            seen++;
        }
        return seen;
    }
};
