class Solution {
public:
    // we compute partial left- and right-products up until
    // the i-th element excluding it.
    // then the result is left * right.
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        vector<int> lp(n), rp(n);
        // lp.reserve(n);
        // rp.reserve(n);

        lp.front() = 1;
        for (int i = 1; i < n; ++i) {
            lp[i] = lp[i-1] * nums[i-1];
        }

        rp.back() = 1;
        for (int i = n-2; i >= 0; --i) {
            rp[i] = rp[i+1] * nums[i+1];
        }

        vector<int> res(n);
        // res.reserve(n);

        for (int i = 0; i < n; ++i) {
            res[i] = lp[i] * rp[i];
        }

        // res.back() = lp.back();
        // int last_rp = 1;
        // for (int i = n-2; i >= 0; --i) {
        //     last_rp = last_rp * nums[i+1];
        //     res[i] = last_rp;
        // }

        return res;
    }
};
