class Solution {
public:
    // 1. find where the array rotates: r (is a min element)
    // 2. at this point we have two sorted sub-arrays: [b; r) + [r, e)
    //     where b = 0, e = n.len()
    // 3. check where the target belongs: left OR right part
    // 4. run binary search on the respective part
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            // searching for the first element <= the last
            if (nums[m] <= nums.back()) r = m;
            else l = m + 1;
        }

        // l is a min element for the array, so it always exists
        int rp = l; // rotation point
        // 1. if target <= nums.back()  => check the right part
        // 2. if target >= nums.front() => check the left part
        // check (1) first, so if there's no any rotation point,
        // ie b == r == 0 => we don't check the left part at all
        if (target <= nums.back()) {
            l = rp; r = nums.size();
        } else if (target >= nums.front()) {
            l = 0; r = rp;
        }

        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] >= target) r = m;
            else l = m + 1;
        }

        if (l == nums.size()) return -1;

        return nums[l] == target ? l : -1;
    }
};
