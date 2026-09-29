class Solution {
public:
    int characterReplacement(string s, int k) {
        array<int, 26> cs{0, 0}; // charset
        for (char c : s) {
            cs[c - 'A'] = 1;
        }

        int mx = 0;
        for (int i = 0; i < std::ssize(cs); ++i) {
            if (cs[i] > 0) {
                mx = max(mx, characterReplacementFor(s, k, i+'A'));
            }
        }
        return mx;
    }

    // find a max string of chars t with max k replacements
    //
    // invariant: [l; r] substring contains all distinct chars (accounting for k replacements)
    // on each iteration check if s[i] == t. if not, consume one replacement and extend the window.
    // when there are no replacement, shrink the window on the left.
    // if shrinked s[l] == t, then one of k's was freed.
    //
    // example: 

    // I.   XYZ k=1 t=X
    //
    //    0 1 2
    // 0.        l=0 r=0 k=1 res=0
    // 1. X Y Z  l=0 r=0 k=1 res=1
    // 2. X Y Z  l=0 r=1 k=0 res=2
    // 3. X Y Z  l=2 r=2 k=0 res=2
    int characterReplacementFor(const string& s, int k, char t) {
        int l = 0, res = 0;
        for (int r = 0; r < std::ssize(s); ++r) {
            if (s[r] != t) {
                // // nothing to replace, we're just counting max substring with one distinct char
                // if (k == 0) ++l;
                // replace the char – borrow rpl
                if (k > 0) --k;
                // if k is drained, move l until k is freed
                else {
                    // shrink until the first freed el (the one != t)
                    while (l < r && s[l] == t) ++l;
                    // start of the window – the next element after the last replaced
                    ++l; 
                }
            }
            res = max(res, r-l+1);
        }
        return res;
    }
};
