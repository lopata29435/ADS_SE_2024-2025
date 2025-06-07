#include <iostream>
#include <vector>
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
    
struct Edge {
    int u, v, weight;
    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
    bool operator==(const Edge &other) const {
        return u == other.u && v == other.v && weight == other.weight;
    }
};

int kruskal(int n, vector<Edge> &g, vector<Edge> &mstEdges, int skip = -1) {
    UnionFind dsu(n);
    int cost = 0;
    int count_edges = 0;
    for (size_t i = 0; i < g.size(); i++) {
        if (i == skip) continue;
        if (dsu.unite(g[i].u, g[i].v)) {
            cost += g[i].weight;
            count_edges++;
            if (skip == -1) mstEdges.push_back(g[i]);
        }
    }

    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> g(m);
    vector<Edge> mstEdges;

    for (int i = 0; i < m; i++) {
        cin >> g[i].u >> g[i].v >> g[i].weight;
        g[i].u--, g[i].v--;
    }
    
    sort(g.begin(), g.end());
    int S1 = kruskal(n, g, mstEdges);
    
    vector<int> costs;
    for (const auto &e : mstEdges) {
        int skip_index = find(g.begin(), g.end(), e) - g.begin();
        int temp = kruskal(n, g, mstEdges, skip_index);
        costs.push_back(temp);
    }

    sort(costs.begin(), costs.end());
    int S2 = (costs.size() >= 1) ? costs[0] : S1;

    cout << S1 << " " << S2 << endl;

    return 0;
}