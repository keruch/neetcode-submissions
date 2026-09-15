class Solution {
public:
    // Format: words are no longer than 200 chars =>
    // the first char is the len of the following string
    // char is a byte => it comfortable hold a number < 200 

    string encode(vector<string>& strs) {
        string res;
        for (string& s : strs) {
            res += static_cast<unsigned char>(s.size());
            res += s;
        }
        return res;
    }

    vector<string> decode(string s) {
        vector<string> res;
        for (size_t i = 0; i < s.size(); ) {
            auto to_read = static_cast<unsigned char>(s[i]);
            auto wbegin = s.begin() + i + 1; // +1 – skip word len
            auto wend = wbegin + to_read;
            string word(wbegin, wend);
            cout << word << endl;
            res.push_back(word);
            i += 1 + to_read; // +1 – skip word len
        }
        return res;
    }
};
