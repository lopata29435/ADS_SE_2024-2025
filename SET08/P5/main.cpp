#include <bits/stdc++.h>
using namespace std;

vector<int> dp_prev(4001);
vector<int> dp_cur(4001);

int levenshtein_distance(const string& a, const string& b) {
    int n = a.length();
    int m = b.length();

    for (int j = 0; j <= m; ++j) {
        dp_prev[j] = j;
    }

    for (int i = 1; i <= n; ++i) {
        dp_cur[0] = i;
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp_cur[j] = dp_prev[j - 1];
            } else {
                dp_cur[j] = 1 + min({dp_cur[j - 1], dp_prev[j], dp_prev[j - 1]});
            }
        }
        swap(dp_prev, dp_cur);
    }

    return dp_prev[m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore();

    vector<int> results(n);
    string s1, s2;

    for (int i = 0; i < n; ++i) {
        getline(cin, s1);
        getline(cin, s2);
        results[i] = levenshtein_distance(s1, s2);
    }

    for (int res : results) {
        cout << res << ' ';
    }
    cout << '\n';
    return 0;
}