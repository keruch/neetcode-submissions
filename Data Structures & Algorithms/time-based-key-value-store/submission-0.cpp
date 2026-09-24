class TimeMap {
public:
    // given that "All the timestamps of set are strictly increasing."
    // we can store all values in a plain vector buckets broke down by the key
    // on set we push back to the vector stored by the respective key 
    // on get we search in a respective vector using binary search 
    TimeMap() {}
    
    void set(string key, string value, int timestamp) {
        buckets[key].emplace_back(timestamp, value);
    }
    
    string get(string key, int ts) { 
        auto it = buckets.find(key);
        if (it == buckets.end()) {
            return "";
        }

        vector<tsv>& vals = it->second;
        int l = 0, r = vals.size();

        // searching for the first element i such that n[i]>ts
        // the last element k such that n[k]<=ts is k=i-1
        while (l < r) {
            int m = l + (r - l) / 2;
            if (vals[m].first > ts) r = m;
            else l = m + 1;
        }

        // given ts is smaller than the first available
        if (l == 0) return "";

        // l == vals.size() is a valid case: 
        // return the latest avaiable ts
        return vals[l-1].second;
    }

private:
    using tsv = pair<int, string>;

    unordered_map<string, vector<tsv>> buckets;
};
