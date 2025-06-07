#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
vector<vector<int>> g;

unordered_map<int,int> dfs(int u, int p) {
    if ((g[u].size() == 1 && p != -1) || g[u].empty()) {
        return {{0, abs(a[u] - 0)}, {1, abs(a[u] - 1)}};
    }

    vector<int> ch;
    for (int v : g[u]) if (v != p) ch.push_back(v);

    unordered_map<int,int> res;
    if (ch.size() == 1) {
        auto d = dfs(ch[0], u);
        for (auto &[val,cost] : d) {
            int cur = cost + abs(a[u] - val);
            if (!res.count(val) || res[val] > cur) res[val] = cur;
        }
    } else {
        auto d1 = dfs(ch[0], u);
        auto d2 = dfs(ch[1], u);
        for (auto &[v1,c1] : d1) {
            for (auto &[v2,c2] : d2) {
                int val = v1 + v2;
                int cur = c1 + c2 + abs(a[u] - val);
                if (!res.count(val) || res[val] > cur) res[val] = cur;
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n);
    g.assign(n, {});
    for (int &x : a) cin >> x;
    for (int i = 0; i < n-1; i++) {
        int u,v; cin >> u >> v; u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto r = dfs(0,-1);
    int ans = INT_MAX;
    for (auto &[val,c] : r) ans = min(ans, c);
    cout << ans << "\n";
    return 0;
}
