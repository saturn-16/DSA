class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> ans(n);

        unordered_map<int, long long> count, sum;

        for (int i = 0; i < n; i++) {
            ans[i] += 1LL * i * count[nums[i]] - sum[nums[i]];
            count[nums[i]]++;
            sum[nums[i]] += i;
        }

        count.clear();
        sum.clear();

        for (int i = n - 1; i >= 0; i--) {
            ans[i] += sum[nums[i]] - 1LL * i * count[nums[i]];
            count[nums[i]]++;
            sum[nums[i]] += i;
        }

        return ans;
    }
};