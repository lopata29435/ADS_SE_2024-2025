#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MOD = 1000000007;
    int N;
    cin >> N;

    if (N == 1) {
        cout << 2 << "\n";
        return 0;
    }
    if (N == 2) {
        cout << 3 << "\n";
        return 0;
    }

    long long prev2 = 2;
    long long prev1 = 3;
    long long curr = 0;

    for (int i = 3; i <= N; i++) {
        curr = (prev1 + prev2) % MOD;
        prev2 = prev1;
        prev1 = curr;
    }

    cout << curr << "\n";
    return 0;
}
