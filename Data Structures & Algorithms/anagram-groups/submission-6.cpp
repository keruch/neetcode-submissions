class Solution {
public:
    vector<vector<string>> groupAnagrams(const vector<string>& strs) {
        map<array<int, 26>, vector<string>> groups{};
        for (const string& s : strs) {
            groups[build_charset(s)].push_back(s);
        }

        vector<vector<string>> res;
        res.reserve(groups.size());
        for (auto& [_, v] : groups) {
            res.push_back(move(v));
        }

        return res;
    }

    array<int, 26> build_charset(const string& s) {
        array<int, 26> cs{};
        for (char c : s) {
            ++cs[c - 'a'];
        }
        return cs;
    }
};
