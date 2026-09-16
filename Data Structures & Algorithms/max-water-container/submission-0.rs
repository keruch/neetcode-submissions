impl Solution {
    // we're maximizing min(n[l], n[r]) * (r - l)
    // on each iteration, we move the pointer
    // pointing to the lower bar.
    // so essentially. we're looking for two
    // highest bars but also consider distance between them.
    //
    // the bigger Q: how we ensure we cover all the possible valid cases??
    pub fn max_area(h: Vec<i32>) -> i32 {
        // 2 <= height.length, so fine to len()-1
        let (mut l, mut r) = (0usize, h.len()-1);

        let mut mx = 0;
        while l < r {
            let mut s = 0i32;
            if h[l] < h[r] {
                s = h[l] * (r-l) as i32;
                l += 1;
            } else {
                s = h[r] * (r-l) as i32;
                r = r.saturating_sub(1);
            }
            mx = mx.max(s);
        }

        mx
    }
}
