class Solution {
public:
    // we're maximizing the profit P
    // P = sell_price - buy_price = n[s] - n[b], s >= b
    // n[b] is the min of the array
    // n[s] is the max of the sub-array (b, len(n))
    //
    // proof: say there's b* > b which gives better profit
    // P* = n[s] - n[b*] > n[s] - n[b] 
    // => n[b*] < n[b] => n[b*] is the min of the array
    //
    // same applies to n[s] and max
    int maxProfit(const vector<int>& p) {
        int mn = 0, mx = 0, res = 0;
        for (int i = 0; i < ssize(p); ++i) {
            if (p[i] <= p[mn]) {
                // begin a new window
                mn = i;
                mx = i;
            }
            if (p[i] > p[mx]) {
                mx = i;
            }
            res = max(res, p[mx] - p[mn]);
        }
        return res;
    }
};
