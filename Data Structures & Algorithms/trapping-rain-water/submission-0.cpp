class Solution {
public:
    // the idea it to find a best container for each starting wall (anchor)
    //
    // the algo is two steps:
    // 1. find best containers left-to-right
    // 2. find best right-to-left
    // it's two-sided since at each point we don't know if there's a higher 2nd wall. we can only commit if find a "best" container for the current wall.
    // re "best" - later
    //
    // the algo:
    // 1. start at [i] -> current anchor, we're finding a best container for it
    // 2. move +1 to the right:
    //   - if [i+1] <= [i] => this is an inner part of the container. we fill the accumulator A += [i] + [i-1]
    //   - if [i] < [i+1] => we found the 2nd wall for the i-th anchor. [i+1] is a new anchor, commit A
    //
    // when we reach the end of the input, repeat the same right-to-left
    //
    // this algo gives "best" containers for the anchor – the best 2nd wall for the anchor i is the first j such that [j] > [i] (A <= min([i], [j]) * (j - i)). contradiction proof: say it's not true and 
    // 1. pick k such that [k] > [j] for the 2nd and say it's the best container with the most trapped water: A <= min([i], [k]) * (k - i). now compute piecewise trapped water sum of the same interval i -> j -> k: A1 <= min([i], [j]) * (j - i) = [i](j-i); A1 <= min([j], [k]) * (k - j) = [j](k-j) => A1 + A2 <= [i](j-i) + [j](k-j). due to the assumption, A > A1 + A2. but A <= [i] * (k-i) = [i](k-j) + [i](j-i) < [j](k-j) + [i](j-i) >= A1 + A2 ==> A < A1 + A2. contradiciton.
    // 2. pick k such that [k] <= [j] and k is best => A >= A1+A2. A <= [k](k-i). piecewise A1 + A2 <= [i](j-i) + [k](k-j) >= [k](k-1) >= A ==> A < A1+A2. contradiction.
    //
    // Q: do we need to prove smth else? maybe a line about the left-to-right and right-to-left?
    int trap(vector<int>& h) {
        if (h.size() < 1) {
            return 0;
        }

        int a_idx = 0; // anchor index
        int acc = 0; // accumulator
        int res = 0;
        for (int i = 1; i < h.size(); ++i) {
            // here should be "<", not "<="; otherwise, we miss a commit.
            if (h[i] < h[a_idx]) {
                acc += h[a_idx] - h[i];
            } else {
                a_idx = i;
                res += acc;
                acc = 0;
            }
        }

        a_idx = h.size()-1;
        acc = 0;
        for (int i = h.size()-2; i >= 0; --i) {
            // here we have "<=" not to commit the container with equal-height walls the second time.
            if (h[i] <= h[a_idx]) {
                acc += h[a_idx] - h[i];
            } else {
                a_idx = i;
                res += acc;
                acc = 0;
            }
        }

        return res;
    }
};
