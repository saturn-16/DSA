class Solution {
public:
    static const long long MOD = 1000000007LL;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (A[i][k] == 0) continue;

                long long aik = A[i][k];

                for (int j = 0; j < n; j++) {
                    if (B[k][j] == 0) continue;

                    C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
                }
            }
        }

        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();

        Matrix res(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) res[i][i] = 1;

        while (exp) {
            if (exp & 1) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1;
        }

        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        int S = 2 * m;

        auto UP = [&](int v) {
            return v;
        };

        auto DOWN = [&](int v) {
            return m + v;
        };

        Matrix T(S, vector<long long>(S, 0));

        for (int v = 0; v < m; v++) {

            // up(v) -> down(w), w < v
            for (int w = 0; w < v; w++) {
                T[UP(v)][DOWN(w)] = 1;
            }

            // down(v) -> up(w), w > v
            for (int w = v + 1; w < m; w++) {
                T[DOWN(v)][UP(w)] = 1;
            }
        }

        vector<long long> init(S, 0);

        // Length = 2 states
        for (int v = 0; v < m; v++) {
            init[UP(v)] = v;             // values smaller than v
            init[DOWN(v)] = m - 1 - v;  // values larger than v
        }

        Matrix P = power(T, n - 2);

        vector<long long> finalState(S, 0);

        for (int j = 0; j < S; j++) {
            long long val = 0;

            for (int k = 0; k < S; k++) {
                val = (val + init[k] * P[k][j]) % MOD;
            }

            finalState[j] = val;
        }

        long long ans = 0;

        for (long long x : finalState) {
            ans = (ans + x) % MOD;
        }

        return (int)ans;
    }
};