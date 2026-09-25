class Solution {
public:
    string s;
    int i = 0;

    set<string> combine(set<string>& a, set<string>& b) {
        set<string> res;

        for (auto &x : a) {
            for (auto &y : b) {
                res.insert(x + y);
            }
        }

        return res;
    }

    set<string> sequence() {
        set<string> res = {""};

        while (i < s.size() && s[i] != '}' && s[i] != ',') {
            set<string> cur;

            if (s[i] == '{') {
                i++;
                cur = expression();
                i++;
            } else {
                cur.insert(string(1, s[i]));
                i++;
            }

            res = combine(res, cur);
        }

        return res;
    }

    set<string> expression() {
        set<string> res = sequence();

        while (i < s.size() && s[i] == ',') {
            i++;

            set<string> cur = sequence();

            res.insert(cur.begin(), cur.end());
        }

        return res;
    }

    vector<string> braceExpansionII(string expr) {
        s = expr;
        i = 0;

        set<string> ans = expression();

        return vector<string>(ans.begin(), ans.end());
    }
};