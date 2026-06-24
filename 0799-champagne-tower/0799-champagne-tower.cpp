class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {

        vector<vector<double>> dp(101, vector<double>(101, 0.0));

        dp[0][0] = poured;

        for (int r = 0; r < 100; r++) {
            for (int c = 0; c <= r; c++) {

                if (dp[r][c] > 1.0) {

                    double excess = (dp[r][c] - 1.0) / 2.0;

                    dp[r + 1][c] += excess;
                    dp[r + 1][c + 1] += excess;
                }
            }
        }

        return min(1.0, dp[query_row][query_glass]);
    }
};