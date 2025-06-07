#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> segments(n);
    for (int i = 0; i < n; i++) {
        cin >> segments[i].first >> segments[i].second;
    }

    sort(segments.begin(), segments.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    });

    vector<int> points;
    int i = 0;
    while (i < n) {
        int p = segments[i].second;
        points.push_back(p);

        i++;
        while (i < n && segments[i].first <= p) {
            i++;
        }
    }

    cout << points.size() << "\n";
    for (int x : points) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}
