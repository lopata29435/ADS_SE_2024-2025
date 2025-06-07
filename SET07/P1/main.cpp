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
        
        for (int &i = ptr[u]; i < adj[u].size(); i++) {
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
    
    int n, m;
    cin >> n >> m;
    Dinic dinic(n);
    
    for (int i = 0; i < m; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        dinic.add_edge(u - 1, v - 1, cap);
    }
    
    cout << dinic.max_flow(0, n - 1) << "\n";
    return 0;
}
