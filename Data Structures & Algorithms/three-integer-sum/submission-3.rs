impl Solution {
    // contract: nums is sorted
    fn two_sum(nums: &[i32], target_idx: usize) -> Vec<Vec<i32>> {
        let (mut l, mut r) = (target_idx+1, nums.len()-1);

        let mut res = Vec::new();

        // if only 1 element left after target_idx, will return early
        while l < r {
            // skip duplicating elements
            // mind the borders
            if l > target_idx+1 && nums[l] == nums[l-1] {
                l = l.saturating_add(1);
                continue;
            }
            if r < nums.len()-1 && nums[r] == nums[r+1] {
                r = r.saturating_sub(1);
                continue;
            }

            if nums[l] + nums[r] == -nums[target_idx] {
                let mut v = vec![nums[l], nums[r], nums[target_idx]];
                v.sort_unstable();
                res.push(v);
                l = l.saturating_add(1);
                continue;
            }
            
            if nums[l] + nums[r] < -nums[target_idx] {
                l = l.saturating_add(1);
            } else {
                r = r.saturating_sub(1);
            }
        }

        return res;
    }

    pub fn three_sum(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
        nums.sort_unstable();

        let mut res = Vec::new();
        // len()-1 since we count triplets 
        // if the target has only 1 idx ahead
        // it's safe to return early
        for i in 0..nums.len()-1 {
            // skip duplicates
            if i > 0 && nums[i] == nums[i-1] { continue; }
            let r = Self::two_sum(&nums, i);
            res.extend(r);
        }

        res
    }
}
