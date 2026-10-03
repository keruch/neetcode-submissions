// 20 min thinking
// 20 min testing on paper
// 25 impl & change the design
// + around 1h to realize I had issues & trace & debug
class Solution {
public:
    // notes:
    //
    // - like 'Permutations in String' but need to return the actual substring
    // - the substring is *shortest*
    //   eg: s = "OUZODYXAZV", t = "XYZ"
    //   there are two solutions: "ZODYX" and "YXAZ" and we need the latter
    // - and the solution is unique
    //   there are no inputs like that: s = "ABA", t = "AB"
    // - the first and last chars of the substring should be in t. otherwise,
    //   the substing is longer for nothing
    // - we count duplicates
    //
    // idea:
    // 1. we find the starting point: the 1st i such that s[i] in t – put l and r at i.
    // 2. start building the window: move r and till the charset S until it matches t.
    // 3. once it does – we found the candidate. we cheched all j: j<r and checked
    //    if they are valid. it doesn't make sense to extend the window further since
    //    we need the shortest. instead, we will try to find a shorter window
    // 4. we move l to the next i such that i<=r and s[i] in t. 
    //    repeat from (2) until r>=len(s).
    //
    // invariant: [l, r] doesn't have a full set of t
    //
    // TODO: maybe 1 can be done more efficiently
    //
    // test (old algo):
    // idx: 0123456789
    // s = "OUZODYXAZV" 
    // t = "XYZ"
    // tcs - target charset 
    // wcs - window charset
    //
    // 0. l=2 r=2 wcs=Z tcs=XYZ // first s[i] in t at i=2
    // 1. l=2 r=3 wcs=Z tcs=XYZ // skip O since it's not in t
    // 2. l=2 r=4 wcs=Z tcs=XYZ
    // 3. l=2 r=5 wcs=ZY tcs=XYZ
    // 4. l=2 r=6 wcs=ZYX tcs=XYZ // match! res = r-l+1 = 5
    // -> l=5 r=6 wcs=YX tcs=XYZ // wcs.s[l]-=1 l+=1 while(s[l] not in t) l+=1
    // 5. l=5 r=7 wcs=YX
    // 6. l=5 r=8 wcs=YXZ // match! res = min(res, r-l+1) = 4
    // -> l=6 r=8 wcs=XZ
    // 7. l=6 r=9 wcs=XZ // end
    //
    // edge cases:
    // * t is one char – fine, l=r is a valid string (see iteration 0)
    // * s < t - fine, return early?
    // * no s[i] in t - fine, we don't find a starting point => res=MAX_INT => return ""
    // * s and t are not empty
    //
    // test (current algo):
    // idx: 0123456789
    // s = "OUZODYXAZV" 
    // t = "XYZ"
    // tcs = XYZ - target charset 
    // wcs - window charset
    //
    // 0. l=0 r=0 wcs=
    // 1. l=0 r=1 wcs=
    // 2. l=0 r=2 wcs=Z
    // 3. l=0 r=3 wcs=Z
    // 4. l=0 r=4 wcs=Z
    // -> l=0 r=5 wcs=ZY
    // 5. l=0 r=6 wcs=ZYX // found
    // -> l=3 r=6 wcs=YX
    // ----
    //
    // test 2 (after WA):
    // idx: 0 1 2 3 4 5 6 7 8 9 10 11 12
    // s = "A D O B E C O D E B A  N  C" 
    // t = "ABC"
    // tcs = ABC - target charset 
    // wcs - window charset
    //
    // 0. l=0 r=0 A wcs=A
    // 1. l=0 r=1 D wcs=A
    // 2. l=0 r=3 O wcs=A
    // 3. l=0 r=3 B wcs=AB
    // 4. l=0 r=4 E wcs=AB
    // 5. l=0 r=5 C wcs=ABC // match: ABOBEC
    // -> l=1 r=5 C wcs=BC res=6
    // 6. l=1 r=6 O wcs=BC
    // 7. l=1 r=7 D wcs=BC
    // 8. l=1 r=8 E wcs=BC
    // 9. l=1 r=9 B wcs=BBC // we met B the second time! 
    //      that's why initial condition (tcs == wcs) didn't work 
    //      added unique_chars & filled_chars
    // 10. l=1 r=10 A wcs=ABBC // match!
    //  -> l=4 r=10 A wcs=ABC // 10-3+1 > 6 -> don't save
    //      one more problem: I only more l when r
    //      advances AND 'if' fires. it means that we can 
    //      miss shorter substrings when we have leading duplicates
    // ----
    // 
    //
    // test 3:
    // idx: 0 1 2 3 4 5 6 7 8 9 10 11 12
    // s = "A D O B B C O D E B A  N  C" 
    // t = "ABC"
    // tcs = ABC - target charset 
    // wcs - window charset
    //
    // 0. l=0 r=0 A wcs=A
    // 1. l=0 r=1 D wcs=A
    // 2. l=0 r=3 O wcs=A
    // 3. l=0 r=3 B wcs=AB
    // 4. l=0 r=4 B wcs=ABB
    // 5. l=0 r=5 C wcs=ABBC // match: ABOBEC
    // -> l=1 r=5 C wcs=BBC res=6
    // 6. l=1 r=6 O wcs=BBC
    // 7. l=1 r=7 D wcs=BBC
    // 8. l=1 r=8 E wcs=BBC
    // 9. l=1 r=9 B wcs=BBBC
    // 10. l=1 r=10 A wcs=ABBBC // match!
    //  -> l=4 r=10 A wcs=ABBC // 10-3+1 > 6 -> don't save
    //     unique_chars == filled_chars == 3, keep shriking
    //  -> l=5 r=10 A wcs=ABC // 10-4+1 > 6 -> don't save
    //     unique_chars == filled_chars == 3, keep shriking
    //  -> l=6 r=10 A wcs=AB 
    // 11. l=6 r=11 N wcs=AB
    // 12. l=6 r=12 C wcs=ABC
    //  -> l=10 r=12 C wcs=ac 12-9+1 = 3 < 6 => res = 4
    // ----
    //
    //
    // test 4 (current solution #2):
    // idx: 0 1 2 3 4 5 6 7 8 9 10 11 12
    // s = "A D O B E C O D E B A  N  C" 
    // t = "ABC"
    // tcs = ABC - target charset 
    // wcs - window charset
    // unique = 3
    //
    // 0. l=0 r=0 A filled=1 wcs=A
    // 1. l=0 r=1 D filled=1 wcs=A
    // 2. l=0 r=3 O filled=1 wcs=A
    // 3. l=0 r=3 B filled=2 wcs=AB
    // 4. l=0 r=4 E filled=2 wcs=AB
    // 5. l=0 r=5 C filled=3 wcs=ABC // match: ABOBEC
    // -> l=1 r=5 C filled=2 wcs=BC res=6
    // 6. l=1 r=6 O filled=2 wcs=BC
    // 7. l=1 r=7 D filled=2 wcs=BC
    // 8. l=1 r=8 E filled=2 wcs=BC
    // 9. l=1 r=9 B filled=2 wcs=BBC 
    // 9. l=1 r=10 B filled=3 wcs=ABBC 
    // -> l=4 r=10 filled=3 wcs=ABC // removed s[3]=B
    // -> l=6 r=10 filled=2 wcs=AB // removed s[5]=C
    //     found an issue: I increased filled every time 'met >= tcs[s[r]]'
    //     so I counted duplicates as fills which broke the window
    //     same for 'met < tcs[s[l]]' when shrinking
    //     'filled' should reflect *unique* elements, so 
    //     I added exact match
    // ----
    string minWindow(const string& s, const string& t) {
        array<int, 128> tcs{}, wcs{};
        for (char c : t) ++tcs[c];

        int unique_chars = 0;
        for (int c : tcs) {
            if (c > 0) ++unique_chars;
        }

        int l = 0, res = INT_MAX, rl = 0, rr = 0;
        int filled_chars = 0;
        for (int r = 0; r < std::ssize(s); ++r) {
            int met = ++wcs[s[r]];

            // if s[r] is in t
            // only increase filled_chars on exact match,
            // so we don't increase it on duplicates
            // this hits only ones since met only goes up
            if (tcs[s[r]] > 0 && met == tcs[s[r]]) {
                ++filled_chars;
            }

            // shriking until we break the valid substring
            while (filled_chars == unique_chars) {
                // cout << l << " " << r << " " << s.substr(l, r-l+1) << endl;

                // here the substring is valid
                // commit the result
                if (r-l+1 < res) {
                    res = r-l+1;
                    rl = l;
                    rr = r;
                }

                // try shortening the window
                int met = --wcs[s[l]];
                // only decrease filled_chars on exact match,
                // so we don't decrease it on duplicates
                // this hits only ones since met only goes down here
                if (tcs[s[l]] > 0 && met == tcs[s[l]]-1) --filled_chars;
                ++l;
            }
        }

        if (res == INT_MAX) return "";

        return s.substr(rl, rr-rl+1);
    }
};
