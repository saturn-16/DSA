class Solution {
public:

    int atMostK(vector<int>& nums, int k)
    {
        if (k < 0)
            return 0;

        unordered_map<int, int> mp;

        int l = 0;
        int count = 0;

        for (int r = 0; r < nums.size(); r++)
        {
            // Include current element
            mp[nums[r]]++;

            // Shrink window if more than k distinct integers
            while (mp.size() > k)
            {
                mp[nums[l]]--;

                if (mp[nums[l]] == 0)
                {
                    mp.erase(nums[l]);
                }

                l++;
            }

            // Count all valid subarrays ending at r
            count += (r - l + 1);
        }

        return count;
    }

    int subarraysWithKDistinct(vector<int>& nums, int k)
    {
        return atMostK(nums, k) - atMostK(nums, k - 1);
    }
};