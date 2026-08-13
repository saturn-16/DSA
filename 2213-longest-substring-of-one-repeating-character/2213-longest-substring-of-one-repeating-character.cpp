class Solution {
    struct Node {
        int len, pre, suf, best;
        char lc, rc;
    };

    vector<Node> st;
    string s;

    Node merge(Node a, Node b) {
        Node c;
        c.len = a.len + b.len;
        c.lc = a.lc;
        c.rc = b.rc;
        c.pre = a.pre;
        c.suf = b.suf;
        c.best = max(a.best, b.best);

        if (a.rc == b.lc) {
            c.best = max(c.best, a.suf + b.pre);

            if (a.pre == a.len)
                c.pre = a.len + b.pre;

            if (b.suf == b.len)
                c.suf = b.len + a.suf;
        }

        return c;
    }

    void build(int p, int l, int r) {
        if (l == r) {
            st[p] = {1, 1, 1, 1, s[l], s[l]};
            return;
        }

        int m = (l + r) / 2;
        build(p * 2, l, m);
        build(p * 2 + 1, m + 1, r);
        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, char ch) {
        if (l == r) {
            st[p] = {1, 1, 1, 1, ch, ch};
            return;
        }

        int m = (l + r) / 2;

        if (idx <= m)
            update(p * 2, l, m, idx, ch);
        else
            update(p * 2 + 1, m + 1, r, idx, ch);

        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        this->s = s;
        int n = s.size();

        st.resize(4 * n);
        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(st[1].best);
        }

        return ans;
    }
};