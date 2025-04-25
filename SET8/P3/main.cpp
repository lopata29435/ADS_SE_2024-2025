#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> prefix(const string& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string P, T;
    cin >> P >> T;

    int n = P.size(), m = T.size();
    if (n == 0 || m == 0 || n > m) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> pi = prefix(P);
    vector<int> result;

    int j = 0;
    for (int i = 0; i < m; ++i) {
        while (j > 0 && T[i] != P[j])
            j = pi[j - 1];
        if (T[i] == P[j])
            ++j;
        if (j == n) {
            result.push_back(i - n + 1);
            j = pi[j - 1];
        }
    }

    cout << result.size() << '\n';
    for (int pos : result)
        cout << pos << '\n';

    return 0;
}
