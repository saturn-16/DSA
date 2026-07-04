class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> hash(256, -1);
        int n = s.size();
        int l = 0;
        int r = 0;
        int maxlength = 0;
        while (r < n)
        {
            if(hash[s[r]] != -1)
            {
                if(hash[s[r]]>=l)
                {
                    l = hash[s[r]]+1;
                }
            }
            int length = r-l+1;
            maxlength = max(length, maxlength);
            hash[s[r]] = r;
            r++;
        }
        return maxlength;
    }
    };