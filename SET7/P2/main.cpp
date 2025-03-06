#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Edge {
    int v, flow, cap, rev;
};

class Dinic {
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;
    
public:
    Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}
    
    void add_edge(int u, int v, int cap) {
        adj[u].push_back({v, 0, cap, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
    }
    
    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        queue<int> q;
        q.push(source);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.flow < e.cap && level[e.v] == -1) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[sink] != -1;
    }
    
    int dfs(int u, int sink, int flow) {
        if (u == sink || flow == 0) return flow;
        
        for (int &i = ptr[u]; i < (int)adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (level[e.v] == level[u] + 1 && e.flow < e.cap) {
                int pushed = dfs(e.v, sink, min(flow, e.cap - e.flow));
                if (pushed > 0) {
                    e.flow += pushed;
                    adj[e.v][e.rev].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    
    int max_flow(int source, int sink) {
        int flow = 0;
        while (bfs(source, sink)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(source, sink, INT_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    unordered_map<string, int> name_to_idx;
    int idx = 0;

    vector<pair<int, int>> edges;

    for (int i = 0; i < m; ++i) {
        string u, v;
        cin >> u >> v;
        if (name_to_idx.find(u) == name_to_idx.end()) {
            name_to_idx[u] = idx++;
        }
        if (name_to_idx.find(v) == name_to_idx.end()) {
            name_to_idx[v] = idx++;
        }
        edges.push_back({name_to_idx[u], name_to_idx[v]});
    }

    vector<pair<int, int>> requests;
    for (int i = 0; i < k; ++i) {
        string a, b;
        cin >> a >> b;
        requests.push_back({name_to_idx[a], name_to_idx[b]});
    }

    for (const auto &req : requests) {
        int a = req.first, b = req.second;
        if (a == -1 || b == -1) {
            cout << 0 << '\n';
            continue;
        }

        Dinic dinic(idx);
        for (const auto &edge : edges) {
            dinic.add_edge(edge.first, edge.second, 1);
            dinic.add_edge(edge.second, edge.first, 1);
        }

        cout << dinic.max_flow(a, b) << '\n';
    }

    return 0;
}