#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int capacity;
    bool is_original;
    int id;
};

vector<vector<Edge>> graph;
vector<int> level;
vector<int> ptr;
int edge_counter = 0;

void add_edge(int u, int v) {
    Edge forward = {v, (int)graph[v].size(), 1, true, edge_counter++};
    Edge backward = {u, (int)graph[u].size(), 0, false, -1};
    graph[u].push_back(forward);
    graph[v].push_back(backward);
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (Edge& e : graph[u]) {
            if (e.capacity > 0 && level[e.to] == -1) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
                if (e.to == t) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int t, int flow) {
    if (u == t) return flow;
    while (ptr[u] < graph[u].size()) {
        Edge& e = graph[u][ptr[u]];
        if (e.capacity > 0 && level[e.to] == level[u] + 1) {
            int pushed = dfs(e.to, t, min(flow, e.capacity));
            if (pushed > 0) {
                e.capacity -= pushed;
                graph[e.to][e.rev].capacity += pushed;
                return pushed;
            }
        }
        ptr[u]++;
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        fill(ptr.begin(), ptr.end(), 0);
        int pushed;
        do {
            pushed = dfs(s, t, INT_MAX);
            flow += pushed;
        } while (pushed > 0);
    }
    return flow;
}

vector<int> find_path(int s, int t, unordered_set<int>& used_edges) {
    vector<int> parent(graph.size(), -1);
    vector<int> edge_used(graph.size(), -1);
    queue<int> q;
    q.push(s);
    parent[s] = -2;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == t) break;
        for (int i = 0; i < graph[u].size(); ++i) {
            Edge& e = graph[u][i];
            if (e.is_original && e.capacity == 0 && !used_edges.count(e.id)) {
                int v = e.to;
                if (parent[v] == -1) {
                    parent[v] = u;
                    edge_used[v] = e.id;
                    q.push(v);
                }
            }
        }
    }
    if (parent[t] == -1) return {};
    vector<int> path;
    int current = t;
    while (current != s) {
        path.push_back(current);
        int e_id = edge_used[current];
        if (e_id != -1) used_edges.insert(e_id);
        current = parent[current];
        if (current == -1) return {};
    }
    path.push_back(s);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, a, h;
    cin >> n >> m >> a >> h;

    graph.resize(n + 1);
    level.resize(n + 1);
    ptr.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        add_edge(x, y);
    }

    int original_flow = max_flow(a, h);
    if (original_flow < 2) {
        cout << "NO\n";
        return 0;
    }

    unordered_set<int> used_edges;
    vector<int> path1 = find_path(a, h, used_edges);
    if (path1.empty()) {
        cout << "NO\n";
        return 0;
    }

    vector<int> path2 = find_path(a, h, used_edges);
    if (path2.empty()) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    for (size_t i = 0; i < path1.size(); ++i) {
        cout << path1[i] << (i + 1 == path1.size() ? "\n" : " ");
    }
    for (size_t i = 0; i < path2.size(); ++i) {
        cout << path2[i] << (i + 1 == path2.size() ? "\n" : " ");
    }

    return 0;
}