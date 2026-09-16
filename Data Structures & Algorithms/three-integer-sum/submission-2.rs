impl Solution {
    // contract: nums is sorted
    fn two_sum(nums: &[i32], target_idx: usize) -> Vec<Vec<i32>> {
        let (mut l, mut r) = (0usize, nums.len()-1);
        let mut res = Vec::new();

        while l < r {
            if l == target_idx {
                l = l.saturating_add(1);
                continue;
            }
            if r == target_idx {
                r = r.saturating_sub(1);
                continue;
            }

            if nums[l] + nums[r] == -nums[target_idx] {
                // return immediately once we have a result.
                // it has no effect to keep iterating further:
                // moving l to right increases the sum (or stays the same
                // if there are duplicates)
                // moving r to left decresaes the sum
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

        nums.iter().enumerate().fold(HashSet::new(), |mut r, (i, _)| {
            for res in Self::two_sum(&nums, i).into_iter() {
                if res.len() > 0 {
                   r.insert(res);
                }
            }
            r
        }).into_iter().collect()
    }
}
