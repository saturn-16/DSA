class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        
        int m = mat.size();
        int n = mat[0].size();

        k %= n;

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                int newPos;

                if (i % 2 == 0) {
                    // left shift
                    newPos = (j + k) % n;
                } else {
                    // right shift
                    newPos = (j - k + n) % n;
                }

                if (mat[i][j] != mat[i][newPos])
                    return false;
            }
        }

        return true;
    }
};