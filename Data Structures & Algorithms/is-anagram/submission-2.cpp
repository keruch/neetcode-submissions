class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> ss;
        ss.reserve(s.size());
        for (const auto& c : s) {
            ++ss[c];
        }

        for (const auto& c : t) {
            auto node = ss.extract(c);
            if (node.empty()) return false;
            if (--node.mapped() > 0) {
                ss.insert(std::move(node)); 
            }
        }

        return ss.empty();
    }
};
