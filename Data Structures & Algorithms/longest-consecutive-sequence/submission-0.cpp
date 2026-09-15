class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int m = 0;
        unordered_set<int> nums_hs;
        // ?? - nums_hs.insert_range(nums.begin(), nums.end());

        for (int n : nums) {
            nums_hs.insert(n);
        }

        unordered_set<int> viewed;
        for (int n : nums_hs) {
            if (!nums_hs.contains(n-1) && !viewed.contains(n)) {
                m = max(m, view(n, nums_hs, viewed));
            }
        }

        return m;
    }

    // contract: `nums` always contains `n`
    int view(const int n, const unordered_set<int>& nums, unordered_set<int>& viewed) {
        int seen = 1;
        while (nums.contains(n+seen)) {
            viewed.insert(n+seen);
            seen++;
        }
        return seen;
    }
};
