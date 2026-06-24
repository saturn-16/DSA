class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {

        int m = coins.size();
        int n = coins[0].size();

        const long long NEG = -1e18;

        vector<vector<vector<long long>>> dp(
            m,
            vector<vector<long long>>(n, vector<long long>(3, NEG))
        );

        // Start cell
        if (coins[0][0] >= 0) {
            dp[0][0][0] = coins[0][0];
        } else {
            dp[0][0][0] = coins[0][0];
            dp[0][0][1] = 0; // neutralize start robber
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0) continue;

                for (int used = 0; used <= 2; used++) {

                    long long best = NEG;

                    if (i > 0)
                        best = max(best, dp[i - 1][j][used]);

                    if (j > 0)
                        best = max(best, dp[i][j - 1][used]);

                    if (best == NEG) continue;

                    // Take cell normally
                    dp[i][j][used] =
                        max(dp[i][j][used],
                            best + coins[i][j]);
                }

                // Neutralize robber if negative
                if (coins[i][j] < 0) {

                    for (int used = 1; used <= 2; used++) {

                        long long best = NEG;

                        if (i > 0)
                            best = max(best,
                                       dp[i - 1][j][used - 1]);

                        if (j > 0)
                            best = max(best,
                                       dp[i][j - 1][used - 1]);

                        if (best == NEG) continue;

                        dp[i][j][used] =
                            max(dp[i][j][used], best);
                    }
                }
            }
        }

        long long ans = max({
            dp[m - 1][n - 1][0],
            dp[m - 1][n - 1][1],
            dp[m - 1][n - 1][2]
        });

        return (int)ans;
    }
};