#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    if (n == 0) {
        cout << "0.0000\n";
        return 0;
    }

    struct Interval {
        double b, e, w;
    };
    vector<Interval> intervals;
    intervals.reserve(n);

    for (int i = 0; i < n; i++) {
        double bi, ei, wi;
        cin >> bi >> ei >> wi;
        intervals.push_back({bi, ei, wi});
    }

    sort(intervals.begin(), intervals.end(),
         [](const Interval &a, const Interval &b) {
             return a.e < b.e;
         });

    vector<double> ends(n);
    for (int i = 0; i < n; i++) {
        ends[i] = intervals[i].e;
    }

    vector<double> dp(n + 1, 0.0);

    for (int i = 1; i <= n; i++) {
        double bi = intervals[i - 1].b;
        double wi = intervals[i - 1].w;

        auto it = upper_bound(ends.begin(), ends.end(), bi);
        int cnt = int(it - ends.begin()); 

        dp[i] = max(dp[i - 1], dp[cnt] + wi);
    }

    cout << fixed << setprecision(4) << dp[n] << "\n";
    return 0;
}
