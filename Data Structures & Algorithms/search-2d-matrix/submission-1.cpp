class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mtx, int target) {
        // m and n are always >= 1

        // binary search through the rows
        // searching for the fist row that > target 
        int l = 0, r = mtx.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            if (mtx[m][0] > target) r = m;
            else l = m + 1;
        }

        // target < the very first element
        if (l == 0) {
            return false;
        }

        // l: idx of the first row > target =>
        // l-1: idx of the last row <= target
        int tr = l-1;

        // if l == mtx.size():
        // - the last row is suitable 
        // - suitable row not found at all
        // check the last row

        l = 0, r = mtx[tr].size();
        if (!(mtx[tr][l] <= target && target <= mtx[tr][r-1])) {
            // the last row is not suitable => suitable row not found
            return false;
        }

        // binary seach through the columns
        // searching for the first column that >= target
        while (l < r) {
            int m = l + (r - l) / 2;
            if (mtx[tr][m] >= target) r = m;
            else l = m + 1;
        }

        // not found
        if (l == mtx[tr].size()) {
            return false;
        }

        return mtx[tr][l] == target;
    }
};
