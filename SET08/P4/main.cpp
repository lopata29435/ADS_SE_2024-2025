#include <bits/stdc++.h>
using namespace std;

#define int long long

const int ALPHABET_SIZE = 256;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string P, T;
    cin >> P >> T;

    int m = P.size(), n = T.size();

    if (m == 0 || n == 0 || m > n) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> shift(ALPHABET_SIZE, m);
    for (int i = 0; i < m - 1; ++i) {
        shift[(unsigned char)P[i]] = m - i - 1;
    }

    vector<int> result;
    int i = 0;

    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && P[j] == T[i + j]) {
            --j;
        }
        if (j < 0) {
            result.push_back(i);
            i += shift[(unsigned char)T[i + m - 1]];
        } else {
            i += shift[(unsigned char)T[i + m - 1]];
        }
    }

    cout << result.size() << '\n';
    for (int pos : result) {
        cout << pos << '\n';
    }

    return 0;
}
