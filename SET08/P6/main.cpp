#include <bits/stdc++.h>
using namespace std;

long long manacer(const string &s) {
    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }

    int n = t.size();
    vector<int> p(n, 0);
    int c = 0, r = 0;
    long long count = 0;

    for (int i = 0; i < n; i++) {
        int mirror = 2 * c - i;

        if (i < r) {
            p[i] = min(r - i, p[mirror]);
        }

        while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 && t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }

        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }

        count += (p[i] + 1) / 2;
    }

    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;

    cout << manacer(s) << endl;

    return 0;
}