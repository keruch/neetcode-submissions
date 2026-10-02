class Solution {
public:
    // 1. build a charset of s1 – S1.
    // 2. maintain a window [l, r] over s2 with its own charset S2.
    //    - extend: add a new char to S2
    //    - shrink: remove a char from S2
    //    - r-l+1 == len(s1)
    // 3. on each iteration, cmp S1 and S2. 
    //    if match – return true; otherwise slide.
    //
    // idea: for each r, check if r is the end of the substring built of S1 chars.
    //
    // invariants:
    // * r-l+1 == len(s1)
    // * S2 contains all chars of [l, r]
    //
    // edge cases:
    // * repeating chars: s1='aaa', s2='aabaaa'
    // * 1 char s1: s1='a', s2='bca'
    // * s1 > s2 => false
    //
    // notes:
    // * r-l+1 == len(s1) - no need to check shorter/longer windows
    // * output is true/false, so no need to care about indexes
    bool checkInclusion(string s1, string s2) {
        array<int, 26> tcs{}; // target char set
        array<int, 26> scs{}; // substring char set

        for (int i = 0; i < std::ssize(s1); ++i) ++tcs[s1[i]-'a'];

        int l = 0;
        for (int r = 0; r < std::ssize(s2); ++r) {
            ++scs[s2[r]-'a'];

            // building the initial substring
            if (r-l+1 < std::ssize(s1)) {
                continue;
            }

            // here r-l+1 == len(s1)
            if (scs == tcs) return true;
            
            // no match - slide the window
            --scs[s2[l]-'a'];
            l++;
            // r is moved at the beginning of the loop
            // no need to move it here manually
        }

        // if len(s1)>len(s2), we hit 'continue' on each iteration and return false
        return false;
    }
};
