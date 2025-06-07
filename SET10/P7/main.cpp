#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long L;
    cin >> L >> n;

    vector<long long> cuts(n);
    for (int i = 0; i < n; i++) {
        cin >> cuts[i];
    }

    int m = n + 2;
    vector<long long> A(m);
    A[0] = 0;
    for (int i = 0; i < n; i++) {
        A[i + 1] = cuts[i];
    }
    A[n + 1] = L;

    const long long INF = (long long)1e18;
    vector< vector<long long> > dp(m, vector<long long>(m, 0));

    for (int len = 2; len <= n + 1; len++) {
        for (int i = 0; i + len < m; i++) {
            int j = i + len;
            long long best = INF;
            for (int k = i + 1; k < j; k++) {
                long long cost = dp[i][k] + dp[k][j] + (A[j] - A[i]);
                if (cost < best) best = cost;
            }
            dp[i][j] = (best == INF ? 0 : best);
        }
    }

    cout << dp[0][n + 1] << "\n";
    return 0;
}
