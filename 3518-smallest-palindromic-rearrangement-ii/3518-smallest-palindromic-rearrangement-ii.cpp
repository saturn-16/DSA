class Solution {
public:
    const long long LIM = 1000000;

    vector<int> primes;

    void sieve(int n) {
        vector<bool> isPrime(n + 1, true);
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                if ((long long)i * i <= n) {
                    for (int j = i * i; j <= n; j += i)
                        isPrime[j] = false;
                }
            }
        }
    }

    int exponentInFact(int n, int p) {
        int res = 0;
        while (n) {
            n /= p;
            res += n;
        }
        return res;
    }

    long long powerCap(long long a, int e) {
        long long res = 1;
        while (e--) {
            if (res > LIM / a) return LIM + 1;
            res *= a;
        }
        return res;
    }

    long long countWays(vector<int> &cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ans = 1;

        for (int p : primes) {
            if (p > total) break;

            int exp = exponentInFact(total, p);
            for (int x : cnt)
                exp -= exponentInFact(x, p);

            if (exp == 0) continue;

            long long mul = powerCap(p, exp);

            if (mul > LIM) return LIM + 1;

            if (ans > LIM / mul) return LIM + 1;

            ans *= mul;
        }

        return min(ans, LIM + 1);
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26, 0);
        char mid = 0;

        int m = 0;
        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            m += half[i];
            if (freq[i] % 2)
                mid = char('a' + i);
        }

        sieve(m);

        if (countWays(half) < k)
            return "";

        string left;

        for (int pos = 0; pos < m; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0)
                    continue;

                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid)
            return left + string(1, mid) + right;

        return left + right;
    }
};