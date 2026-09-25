class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) return findMedianSortedArrays(b, a);

        int m = a.size(), n = b.size();
        int half = (m + n + 1) / 2;
        int lo = 0, hi = m;

        while (lo <= hi) {
            int i = lo + (hi - lo) / 2;
            int j = half - i;

            long aL = (i == 0) ? LONG_MIN : a[i-1];
            long aR = (i == m) ? LONG_MAX : a[i];
            long bL = (j == 0) ? LONG_MIN : b[j-1];
            long bR = (j == n) ? LONG_MAX : b[j];

            if (aL <= bR && bL <= aR) {
                if ((m + n) % 2) return max(aL, bL);
                return (max(aL, bL) + min(aR, bR)) / 2.0;
            }
            if (aL > bR) hi = i - 1;
            else         lo = i + 1;
        }
        return 0.0;
    }
};