class Solution {
public:
    string simplifyPath(string path) {

        vector<string> st;
        string curr;

        stringstream ss(path);

        while (getline(ss, curr, '/')) {

            if (curr == "" || curr == ".")
                continue;

            if (curr == "..") {
                if (!st.empty())
                    st.pop_back();
            }
            else {
                st.push_back(curr);
            }
        }

        if (st.empty())
            return "/";

        string ans;

        for (string dir : st) {
            ans += "/" + dir;
        }

        return ans;
    }
};