class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            vector<int> freq(26, 0);

            for (int j = i; j < n; j++) {
                freq[s[j] - 'a']++;

                int target = 0;
                bool balanced = true;

                for (int k = 0; k < 26; k++) {
                    if (freq[k] > 0) {
                        if (target == 0)
                            target = freq[k];
                        else if (freq[k] != target) {
                            balanced = false;
                            break;
                        }
                    }
                }

                if (balanced) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};