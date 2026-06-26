class Solution {
public:
    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int sz) {
            n = sz;
            bit.assign(n + 1, 0);
        }

        void update(int idx, int val) {
            while (idx <= n) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }

        int query(int idx) {
            int res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
    };

    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        int offset = n + 2;
        Fenwick ft(2 * n + 5);

        long long ans = 0;
        int pref = 0;

        // prefix sum = 0
        ft.update(offset, 1);

        for (int x : nums) {
            if (x == target)
                pref++;
            else
                pref--;

            int idx = pref + offset;

            // count previous prefix sums < current prefix sum
            ans += ft.query(idx - 1);

            ft.update(idx, 1);
        }

        return ans;
    }
};