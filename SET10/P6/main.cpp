#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> weight(N), value(N);
    for (int i = 0; i < N; i++) {
        cin >> weight[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> value[i];
    }

    vector<int> dp(M + 1, 0);
    for (int i = 0; i < N; i++) {
        int w = weight[i];
        int v = value[i];
        for (int cap = M; cap >= w; cap--) {
            dp[cap] = max(dp[cap], dp[cap - w] + v);
        }
    }

    cout << dp[M] << "\n";
    return 0;
}
