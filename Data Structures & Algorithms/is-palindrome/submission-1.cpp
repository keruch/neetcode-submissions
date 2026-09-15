#include <cctype>

class Solution {
public:

    bool isPalindrome(string s) {
        for (size_t l = 0, r = s.size()-1; l < r; ) {
            auto lc = tolower(s[l]);
            auto rc = tolower(s[r]);

            if ((lc > 'z' || lc < 'a') && (lc < '0' || lc > '9')){
                l++;
                continue;
            }

            if ((rc > 'z' || rc < 'a') && (rc < '0' || rc > '9')) {
                r--;
                continue;
            }

            if (lc != rc) {
                return false;
            }

            r--;
            l++;
        }
        return true;
    }
};
