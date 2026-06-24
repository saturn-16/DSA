class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 1;

        // Case 1: only one distinct character
        int run = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i - 1]) {
                run++;
            } else {
                run = 1;
            }
            ans = max(ans, run);
        }

        long long A = 0, B = 0, C = 0;

        unordered_map<long long, int> ab;
        unordered_map<long long, int> ac;
        unordered_map<long long, int> bc;
        unordered_map<long long, int> abc;

        auto key2 = [](long long x, long long y) -> long long {
            return ((x + 100000LL) << 20) ^ (y + 100000LL);
        };

        auto keyABC = [](long long x, long long y) -> long long {
            return ((x + 100000LL) << 20) ^ (y + 100000LL);
        };

        ab[key2(0, 0)] = 0;     // (A-B, C)
        ac[key2(0, 0)] = 0;     // (A-C, B)
        bc[key2(0, 0)] = 0;     // (B-C, A)
        abc[keyABC(0, 0)] = 0;  // (A-B, A-C)

        for (int i = 1; i <= n; i++) {
            char ch = s[i - 1];

            if (ch == 'a') A++;
            else if (ch == 'b') B++;
            else C++;

            // a & b only
            long long k1 = key2(A - B, C);
            if (ab.count(k1))
                ans = max(ans, i - ab[k1]);
            else
                ab[k1] = i;

            // a & c only
            long long k2 = key2(A - C, B);
            if (ac.count(k2))
                ans = max(ans, i - ac[k2]);
            else
                ac[k2] = i;

            // b & c only
            long long k3 = key2(B - C, A);
            if (bc.count(k3))
                ans = max(ans, i - bc[k3]);
            else
                bc[k3] = i;

            // a, b & c all equal
            long long k4 = keyABC(A - B, A - C);
            if (abc.count(k4))
                ans = max(ans, i - abc[k4]);
            else
                abc[k4] = i;
        }

        return ans;
    }
};