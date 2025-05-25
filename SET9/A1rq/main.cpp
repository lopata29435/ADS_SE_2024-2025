#include <bits/stdc++.h>
using namespace std;

constexpr int R = 256;
constexpr int THRESH = 74;

inline int charAt(const string &s, int d) {
    return (d < (int)s.size()) ? (unsigned char)s[d] : -1;
}

void quick3way(vector<string> &a, int lo, int hi, int d) {
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
    quick3way(a, lo, lt - 1, d);
    if (pivot >= 0)
        quick3way(a, lt, gt, d + 1);
    quick3way(a, gt + 1, hi, d);
}

void msdRadixSort(vector<string> &a, int lo, int hi, int d, vector<string> &aux) {
    if (lo >= hi) return;
    int len = hi - lo + 1;
    if (len < THRESH) {
        quick3way(a, lo, hi, d);
        return;
    }
    vector<int> count(R + 2, 0);

    for (int i = lo; i <= hi; ++i) {
        int c = charAt(a[i], d) + 1;
        count[c + 1]++;
    }
    for (int r = 0; r <= R; ++r) {
        count[r + 1] += count[r];
    }
    for (int i = lo; i <= hi; ++i) {
        int c = charAt(a[i], d) + 1;
        aux[count[c]++] = move(a[i]);
    }
    for (int i = lo; i <= hi; ++i) {
        a[i] = move(aux[i - lo]);
    }
    for (int r = 0; r <= R; ++r) {
        int start = lo + (r == 0 ? 0 : count[r - 1]);
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
