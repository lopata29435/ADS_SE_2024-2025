#include <bits/stdc++.h>
using namespace std;

inline int charCode(const string &s, int d) {
    return (d < (int)s.size()) ? (unsigned char)s[d] + 1 : 0;
}

void msdRadixSort(vector<string> &a, int lo, int hi, int d, vector<string> &aux) {
    if (lo >= hi) return;
    const int R = 256;
    vector<int> count(R + 2, 0);

    for (int i = lo; i <= hi; ++i) {
        int c = charCode(a[i], d);
        count[c + 1]++;
    }
    for (int r = 0; r < R + 1; ++r) {
        count[r + 1] += count[r];
    }
    for (int i = lo; i <= hi; ++i) {
        int c = charCode(a[i], d);
        aux[count[c]++] = move(a[i]);
    }
    for (int i = lo; i <= hi; ++i) {
        a[i] = move(aux[i - lo]);
    }
    for (int r = 0; r < R + 1; ++r) {
        int start = lo + count[r > 0 ? r - 1 : 0];
        int end   = lo + count[r] - 1;
        if (start <= end) {
            msdRadixSort(a, start, end, d + 1, aux);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<string> aux(n);
    msdRadixSort(a, 0, n - 1, 0, aux);

    for (const auto &s : a) {
        cout << s << "\n";
    }
    return 0;
}
