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

    string p;
    cin >> p;
    int n = p.size();
    auto pi = prefix(p);

    int period = n - pi[n - 1];
    cout << period << '\n';

    return 0;
}