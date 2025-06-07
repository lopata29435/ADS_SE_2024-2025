#include <bits/stdc++.h>
using namespace std;

struct Story {
    long long c, w;
    double ratio;
    
    Story(long long c, long long w) : c(c), w(w) {
        ratio = (double)c / w;
    }
    
    bool operator<(const Story &other) const {
        return ratio > other.ratio;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    long long W;
    cin >> n >> W;

    vector<Story> stories;
    for (int i = 0; i < n; ++i) {
        long long c, w;
        cin >> c >> w;
        stories.emplace_back(c, w);
    }

    sort(stories.begin(), stories.end());

    double totalDiscussion = 0.0;
    for (const auto &s : stories) {
        if (W == 0) break;

        if (W >= s.w) {
            totalDiscussion += s.c;
            W -= s.w;
        } else {
            totalDiscussion += s.ratio * W;
            W = 0;
        }
    }

    cout << fixed << setprecision(10) << totalDiscussion << '\n';
    return 0;
}
