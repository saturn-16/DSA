class Solution {
public:
    int longestPalindrome(string s) {

        unordered_map<char, int> freq;

        for (char c : s)
            freq[c]++;

        int ans = 0;
        bool odd = false;

        for (auto &it : freq) {

            if (it.second % 2 == 0)
                ans += it.second;
            else {
                ans += it.second - 1;
                odd = true;
            }
        }

        if (odd)
            ans++;

        return ans;
    }
};