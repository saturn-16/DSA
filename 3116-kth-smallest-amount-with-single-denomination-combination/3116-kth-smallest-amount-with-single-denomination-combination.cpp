class Solution {
public:
    using ll = long long;

    ll gcd(ll a, ll b) {
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    ll lcm(ll a, ll b) {
        return a / gcd(a, b) * b;
    }

    ll count(ll x, vector<int>& coins) {
        ll ans = 0;
        int n = coins.size();

        for (int mask = 1; mask < (1 << n); mask++) {
            ll cur = 1;
            bool ok = true;
            int bits = 0;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;
                    cur = lcm(cur, (ll)coins[i]);

                    if (cur > x) {
                        ok = false;
                        break;
                    }
                }
            }

            if (!ok) continue;

            ll ways = x / cur;

            if (bits & 1)
                ans += ways;
            else
                ans -= ways;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        ll low = 1;
        ll high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            ll mid = low + (high - low) / 2;

            if (count(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};