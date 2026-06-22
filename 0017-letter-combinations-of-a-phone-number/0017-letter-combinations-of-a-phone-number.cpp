class Solution {
public:
    vector<string> ans;

    void backtrack(string digits, int index, string curr,
                   vector<string>& mp) {

        if (index == digits.size()) {
            ans.push_back(curr);
            return;
        }

        string letters = mp[digits[index] - '0'];

        for (char ch : letters) {
            backtrack(digits, index + 1, curr + ch, mp);
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};

        vector<string> mp = {
            "", "", "abc", "def", "ghi",
            "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        backtrack(digits, 0, "", mp);

        return ans;
    }
};