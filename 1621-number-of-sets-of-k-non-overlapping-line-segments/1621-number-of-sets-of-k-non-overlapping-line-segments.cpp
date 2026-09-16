class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;
        long long ans = 1;

        int r = 2 * k;
        for (int i = 1; i <= r; i++) {
            ans = ans * (n + k - i) % MOD;

            long long inv = 1;
            long long a = i, b = MOD - 2;

            while (b) {
                if (b & 1)
                    inv = inv * a % MOD;
                a = a * a % MOD;
                b >>= 1;
            }

            ans = ans * inv % MOD;
        }

        return ans;
    }
};