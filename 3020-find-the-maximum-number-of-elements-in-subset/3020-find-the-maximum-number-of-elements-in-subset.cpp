class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;

        for (int x : nums)
            cnt[x]++;

        int ans = 1;

        // Special case for 1
        if (cnt.count(1)) {
            int c = cnt[1];
            ans = max(ans, (c % 2 == 0) ? c - 1 : c);
        }

        for (auto &[start, f] : cnt) {
            if (start == 1) continue;

            long long cur = start;
            int len = 0;

            while (true) {
                auto it = cnt.find(cur);

                if (it == cnt.end()) {
                    len--;
                    break;
                }

                if (it->second == 1) {
                    len++;
                    break;
                }

                len += 2;

                if (cur > 1000000000LL) break;
                if (cur > 1000000000000000000LL / cur) break;

                cur = cur * cur;
            }

            ans = max(ans, len);
        }

        return ans;
    }
};