class Solution {
public:
    vector<int> parent, rank_;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return;

        if (rank_[px] < rank_[py])
            swap(px, py);

        parent[py] = px;

        if (rank_[px] == rank_[py])
            rank_[px]++;
    }

    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {

        parent.resize(n);
        rank_.assign(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        // Connect adjacent indices if possible
        for (int i = 0; i < n - 1; i++) {
            if (nums[i + 1] - nums[i] <= maxDiff)
                unite(i, i + 1);
        }

        vector<bool> ans;

        for (auto &q : queries) {
            ans.push_back(find(q[0]) == find(q[1]));
        }

        return ans;
    }
};