#include <numeric>

class Solution {
public:
    // k is in [1; max(n)]
    // k == 1 => h = sum(n_i)
    // k == max(n) => h = len(n)
    // 
    // straightforward solution:
    // - binary search over k
    // - searching for k such that P(k) = {H(k) <= h} where H(k) is a func
    //   returning h_k computed for k.
    //
    // P(max(n)) is always true since H(max(n)) = len(n) <= h due to the constraints
    // use the r-exluded binary search. if the answer is not found in [1; r)
    // then l defaults to r = max(n) which is always a valid answer.
    //
    // H(k) is O(n) – iterates over all the elements to compute h_k
    // binary search is O(log max(n))
    // => time is O(n log max(n))
    //
    // Q: how to prove there's no better solution??
    int minEatingSpeed(vector<int>& n, int h) {
        int r = *std::max_element(n.begin(), n.end());
        int l = 1;

        while (l < r) {
            int m = l + (r - l) / 2;
            if (H(n, m) <= h) r = m;
            else l = m + 1;
        }

        return l;
    }

    int H(const vector<int>& n, int k) {
        return std::accumulate(n.begin(), n.end(), 0, [k](int acc, int v) { 
            int h = v / k + ((v % k) != 0);
            return acc + h; 
        });
    }
};
