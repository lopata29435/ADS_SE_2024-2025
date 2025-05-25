#include <bits/stdc++.h>
using namespace std;

inline int charAt(const string &s, int d) {
    return (d < (int)s.size()) ? (unsigned char)s[d] : -1;
}

void msd3way(vector<string> &a, int lo, int hi, int d) {
    if (lo >= hi) return;
    int lt = lo, gt = hi;
    int pivot = charAt(a[lo], d);
    int i = lo + 1;
    while (i <= gt) {
        int c = charAt(a[i], d);
        if (c < pivot) {
            swap(a[lt++], a[i++]);
        } else if (c > pivot) {
            swap(a[i], a[gt--]);
        } else {
            i++;
        }
    }
    msd3way(a, lo, lt - 1, d);
    if (pivot >= 0)
        msd3way(a, lt, gt, d + 1);
    msd3way(a, gt + 1, hi, d);
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

    msd3way(a, 0, n - 1, 0);

    for (const auto &s : a) {
        cout << s << "\n";
    }
    return 0;
}
