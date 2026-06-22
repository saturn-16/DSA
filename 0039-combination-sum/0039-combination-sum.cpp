class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void backtrack(vector<int>& candidates, int target, int index) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }

        if (index >= candidates.size() || target < 0)
            return;

        path.push_back(candidates[index]);
        backtrack(candidates, target - candidates[index], index);
        path.pop_back();

        backtrack(candidates, target, index + 1);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, target, 0);
        return ans;
    }
};