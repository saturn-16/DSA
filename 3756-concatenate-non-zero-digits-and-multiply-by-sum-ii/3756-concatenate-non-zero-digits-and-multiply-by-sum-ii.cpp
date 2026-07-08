class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1000000007LL;
        int m = s.size();
        
        // cnt[i] = number of non-zero digits in s[0..i-1]
        vector<int> cnt(m + 1, 0);
        // val[j] = value (mod MOD) of the number formed by the first j non-zero digits
        // dsum[j] = sum of the first j non-zero digits (actual sum, small values)
        vector<long long> val(m + 1, 0);
        vector<long long> dsum(m + 1, 0);
        
        for (int i = 0; i < m; i++) {
            int d = s[i] - '0';
            if (d != 0) {
                cnt[i + 1] = cnt[i] + 1;
                val[cnt[i + 1]] = (val[cnt[i]] * 10 + d) % MOD;
                dsum[cnt[i + 1]] = dsum[cnt[i]] + d;
            } else {
                cnt[i + 1] = cnt[i];
            }
        }
        
        int maxNZ = cnt[m];
        vector<long long> pw10(maxNZ + 1);
        pw10[0] = 1;
        for (int j = 1; j <= maxNZ; j++) {
            pw10[j] = (pw10[j - 1] * 10) % MOD;
        }
        
        int q = queries.size();
        vector<int> ans(q);
        
        for (int i = 0; i < q; i++) {
            int l = queries[i][0], r = queries[i][1];
            int a = cnt[l];
            int b = cnt[r + 1];
            int k = b - a;
            
            if (k == 0) {
                ans[i] = 0;
                continue;
            }
            
            long long x = ((val[b] - val[a] * pw10[k]) % MOD + MOD) % MOD;
            long long sum = dsum[b] - dsum[a];
            long long result = (x * (sum % MOD)) % MOD;
            
            ans[i] = (int) result;
        }
        
        return ans;
    }
};