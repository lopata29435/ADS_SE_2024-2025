#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent;
    vector<int> rank;

    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root) return;
        if (rank[x_root] < rank[y_root]) {
            parent[x_root] = y_root;
        } else {
            parent[y_root] = x_root;
            if (rank[x_root] == rank[y_root]) {
                rank[x_root]++;
            }
        }
    }
};

struct Dinic {
    struct Edge {
        int to, rev;
        size_t capacity, flow;
        Edge(int to, int rev, size_t capacity, size_t flow)
            : to(to), rev(rev), capacity(capacity), flow(flow) {}
    };

    vector<vector<Edge>> graph;
    vector<int> level, ptr;
    int n;

    Dinic(int n) : n(n), graph(n), level(n), ptr(n) {}

    void add_edge(int u, int v, size_t capacity) {
        graph[u].emplace_back(v, graph[v].size(), capacity, 0);
        graph[v].emplace_back(u, graph[u].size() - 1, 0, 0);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge &e : graph[u]) {
                if (e.capacity - e.flow > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                    if (e.to == t) return true;
                }
            }
        }
        return false;
    }

    size_t dfs(int u, int t, size_t pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int &i = ptr[u]; i < graph[u].size(); ++i) {
            Edge &e = graph[u][i];
            if (level[e.to] != level[u] + 1 || e.capacity - e.flow == 0) continue;
            size_t res = dfs(e.to, t, min(pushed, e.capacity - e.flow));
            if (res > 0) {
                e.flow += res;
                graph[e.to][e.rev].flow -= res;
                return res;
            }
        }
        return 0;
    }

    size_t max_flow(int s, int t) {
        size_t flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (size_t pushed = dfs(s, t, numeric_limits<size_t>::max())) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    unordered_map<string, int> name_to_idx;
    vector<pair<string, string>> edges, requests;
    int idx = 0;

    auto get_index = [&](const string &name) {
        if (name_to_idx.count(name)) return name_to_idx[name];
        return name_to_idx[name] = idx++;
    };

    for (int i = 0; i < m; ++i) {
        string u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        get_index(u);
        get_index(v);
    }

    for (int i = 0; i < k; ++i) {
        string a, b;
        cin >> a >> b;
        requests.emplace_back(a, b);
        get_index(a);
        get_index(b);
    }

    int total_nodes = idx;
    UnionFind uf(total_nodes);

    for (const auto &edge : edges) {
        int u = name_to_idx[edge.first];
        int v = name_to_idx[edge.second];
        uf.unite(u, v);
    }

    vector<pair<int, int>> directed_edges;
    for (const auto &edge : edges) {
        int u = name_to_idx[edge.first];
        int v = name_to_idx[edge.second];
        directed_edges.emplace_back(u, v);
        directed_edges.emplace_back(v, u);
    }

    for (const auto &request : requests) {
        const string &a_str = request.first;
        const string &b_str = request.second;

        if (a_str == b_str) {
            cout << 0 << '\n';
            continue;
        }

        auto it_a = name_to_idx.find(a_str);
        auto it_b = name_to_idx.find(b_str);
        if (it_a == name_to_idx.end() || it_b == name_to_idx.end()) {
            cout << 0 << '\n';
            continue;
        }

        int a = it_a->second;
        int b = it_b->second;

        if (uf.find(a) != uf.find(b)) {
            cout << 0 << '\n';
            continue;
        }

        Dinic dinic(total_nodes);
        for (const auto &e : directed_edges) {
            dinic.add_edge(e.first, e.second, 1);
        }

        cout << dinic.max_flow(a, b) << '\n';
    }

    return 0;
}