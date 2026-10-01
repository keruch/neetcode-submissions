// V1:
// 1.5 hours total
// 15 mins to come up with the idea
// 30 mins to impl it
// 25 mins to debug
// 20 mins to simplify and solve
//
// V2: 
// 1 hour 10 min
// 25 mins to come up with the solution
// 10 min first impl
// 15 min thinking re most_freq
// 5  min hint + realization
// 10 min impl and debug
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
            // Claim: if incrementing cs[s[r]] raises most_freq, the slide doesn't fire this iteration.
            //
            // Contrapositive: if the slide fires, most_freq did not change this iteration. So decrementing 
            // cs[s[l]] during the slide can't be "undoing" an increment that most_freq is currently reflecting 
            // — most_freq came from some earlier, larger count.
            int most_freq = max(most_freq, ++cs[s[r]-'A']);

            // slide if needed
            if (most_freq + k < r - l + 1) {
                // doesn't need to change most_freq, it might be stale
                --cs[s[l]-'A'];
                ++l;
            }

            // compute the result
            // a stale-high most_freq can only wrongly validate a window whose size 
            // we've already recorded legitimately, so res is never overstated.
            res = max(res, r-l+1);

            // the window is always valid at the end of the iteration
            // the window starts valid at r=0
        }

        return res;
    }
};
