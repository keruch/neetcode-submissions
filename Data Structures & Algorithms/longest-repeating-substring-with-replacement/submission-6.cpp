// V1:
// 1.5 hours total
// 15 mins to come up with the idea
// 30 mins to impl it
// 25 mins to debug
// 20 mins to simplify and solve
//
// V2:
class Solution {
public:
    // 1. extend the window: manage a set of all chars in this substring
    // 2. use the set to get the max num of repearing chars -> most freq element
    // 3. keep extending the window while max+k>=len. that case, we replace at most k
    //    chars of max to get the string of len r-l+1. otherwise, it's impossible to 
    //    build such a string. 
    // 4. if max+k<len, shrink – ~remove chars from the set~ – we don't actually need
    //    to shrink. we already found a window of (potentially) max len and it doesn't
    //    make sense to account for shorter substrings, so we slide the entire window at once.
    int characterReplacement(string s, int k) {
        array<int, 26> cs{0, 0}; // charset

        int l = 0, most_freq = 0, res = 0;
        for (int r = 0; r < std::ssize(s); ++r) {
            // check before extending
            // don't use most_freq here since if s[r] == s[l] and we decide to slide
            // then most_freq doesn't change
            int new_most_freq = max(most_freq, ++cs[s[r]-'A']);

            // slide if needed
            if (new_most_freq + k < r - l + 1) {
                // doesn't need to change most_freq, it might be stale
                --cs[s[l]-'A'];
                ++l;
            }

            // extend: compute most freq after sliding
            most_freq = max(most_freq, cs[s[r]-'A']);

            // compute the result
            res = max(res, r-l+1);
        }

        return res;
    }
};
