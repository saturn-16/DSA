class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {

        int l = 0;
        int r = 0;
        int zeroes = 0;
        int maxlength = 0;

        while (r < nums.size())
        {
            // Include the current element in the window
            if (nums[r] == 0)
            {
                zeroes++;
            }

            // Shrink the window until it becomes valid
            while (zeroes > k)
            {
                if (nums[l] == 0)
                {
                    zeroes--;
                }

                l++;
            }

            
            int length = r - l + 1;
            maxlength = max(maxlength, length);

            // Expand the window
            r++;
        }

        return maxlength;
    }
};