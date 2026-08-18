class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {

        int n = nums.size();
        int answer = -1;

        // Try every possible value
        for (int x = 0; x <= 50; x++) {

            int count = 0;

            // Try every subarray of size k
            for (int start = 0; start <= n - k; start++) {

                bool found = false;

                // Check whether x exists in this subarray
                for (int j = start; j < start + k; j++) {

                    if (nums[j] == x) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    count++;
                }
            }

            // x appears in exactly one subarray
            if (count == 1) {
                answer = max(answer, x);
            }
        }

        return answer;
    }
};