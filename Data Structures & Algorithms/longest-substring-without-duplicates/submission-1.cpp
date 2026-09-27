class Solution {
public:
    // build a subscring with no repeating elements 
    //
    // invariant: no repeating elements in the built substring
    //
    // start at index l - fix it, init a set of chars S
    // move index r right. s[r] in S? 
    //   - yes (duplicates detected): remove s[l] from S and ++l – repeat until s[r] not in S
    //   - no: add s[r] to S
    //
    // this way, a substring [l; r] never has duplicates
    // proceed moving r untill the next duplicate or the array end
    // on each iteration, check the len of the substring and commit if >= commited
    //
    //
    // proof (that we found a max substing and count all possible options):
    //
    // for each element i, s[i] is either
    // - a startring char of a substring: we fix i and move r until find the 1st duplicating
    //   => we counted the max substring [i; r] for this char.
    // - a middle char in the existing substiring [l; r] => len([i; r]) < len([l; r])
    // 
    // so we check max substring for each char
    //
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> d;
        int l = 0, res = 0;
        for (int r = 0; r < std::ssize(s); ++r) {
            while (d.contains(s[r])) {
                // fix the invariant – shrink 
                d.erase(s[l]);
                l++;
            }

            // here the invariant is valid, procees
            d.insert(s[r]);
            res = max(res, r-l+1); 
        }
        return res;
    }
};
