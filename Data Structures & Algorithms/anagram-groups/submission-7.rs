impl Solution {
    fn build_charset(s: &str) -> [u32; 26] {
        let mut cs = [0u32; 26];
        for c in s.bytes() {
            cs[(c - b'a') as usize] += 1;
        }
        cs
    }

    pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
        strs.into_iter().fold(
            HashMap::new(), 
            |mut gr: HashMap<[u32; 26], Vec<String>>, s| 
            {
                (*gr.entry(Self::build_charset(&s)).or_default()).push(s);
                gr
            }
        ).into_values().collect()
    }
}
