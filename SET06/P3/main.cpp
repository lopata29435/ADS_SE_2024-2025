#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

class UnionFind {
    public:
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
        }
    
        int find(int v) {
            if (parent[v] == v) return v;
            return parent[v] = find(parent[v]);
        }
    
        bool unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return false;
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
            return true;
        }
    
    private:
        vector<int> parent, rank;
};
    
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    UnionFind uf(n + 1);

    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<pair<string, pair<int, int>>> operations(k);
    for (int i = 0; i < k; ++i) {
        string type;
        int u, v;
        cin >> type >> u >> v;
        operations[i] = {type, {u, v}};
    }

    reverse(operations.begin(), operations.end());

    vector<string> result;
    for (const auto& op : operations) {
        string type = op.first;
        int u = op.second.first;
        int v = op.second.second;

        if (type == "cut") {
            uf.unite(u, v);
        } else if (type == "ask") {
            if (uf.find(u) == uf.find(v)) {
                result.push_back("YES");
            } else {
                result.push_back("NO");
            }
        }
    }

    reverse(result.begin(), result.end());
    for (const string& res : result) {
        cout << res << '\n';
    }

    return 0;
}