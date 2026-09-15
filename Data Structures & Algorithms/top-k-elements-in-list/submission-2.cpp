#include <ranges>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> ns{};
        int mx = 0;
        for (int n : nums) {
            mx = max(mx, ++ns[n]);
        }

        vector<vector<int>> freq(mx+1, vector<int>{});
        for (const auto& [val, fq] : ns) {
            freq[fq].push_back(val);
        }

        vector<int> res;
        res.reserve(k);
        for (const auto& bucket : freq | std::views::reverse) {
            for (int v : bucket) {
                res.push_back(v);
                if (res.size() >= k) return res;
            }
        }

        return res;
    }
};
