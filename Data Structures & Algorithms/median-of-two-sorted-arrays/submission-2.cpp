class Solution {
public:
    double findMedianSortedArrays(vector<int>& n1, vector<int>& n2) {
        int m = n1.size(), n = n2.size();
        if (m > n) {
            return findMedianSortedArrays(n2, n1);
        }

        int h = (m + n) / 2;
        // binary search over cut positions, eg like this:
        // | 1 | 3 | 9 |
        // 0   1   2   3
        int l = 0, r = m+1;
        while (l < r) {
            int mn1 = l + (r - l) / 2;
            int mn2 = h - mn1;

            long ln1 = (mn1 <= 0) ? LONG_MIN : n1[mn1-1];
            long rn1 = (mn1 >= m) ? LONG_MAX : n1[mn1];
            long ln2 = (mn2 <= 0) ? LONG_MIN : n2[mn2-1]; // mn2 in [0; h] since m <= n
            long rn2 = (mn2 >= n) ? LONG_MAX : n2[mn2];

            if (ln1 <= rn2 && ln2 <= rn1) {
                if ((m+n) % 2) return min(rn1, rn2);
                else return static_cast<float>(max(ln1, ln2) + min(rn1, rn2)) / 2;
            }

            if (ln1 > rn2) r = mn1;
            else l = mn1 + 1;
        }

        return 0.0;
    }
};
