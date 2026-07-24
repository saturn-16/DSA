class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int M = 2048;

        bitset<M> dp[4];
        dp[0][0] = 1;

        for (int v : nums) {
            for (int rep = 0; rep < 3; rep++) {
                for (int cnt = 2; cnt >= 0; cnt--) {
                    bitset<M> nxt;
                    for (int x = 0; x < M; x++) {
                        if (dp[cnt][x])
                            nxt[x ^ v] = 1;
                    }
                    dp[cnt + 1] |= nxt;
                }
            }
        }

        return dp[3].count();
    }
};