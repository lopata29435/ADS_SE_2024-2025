#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Edge {
    int u, v, weight;
};

void bellman_ford(int n, vector<Edge>& edges) {
    const long long INF = LLONG_MAX / 2;
    vector<long long> dist(n, INF);
    dist[0] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.weight) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    vector<bool> inNegativeCycle(n, false);
    for (const auto& edge : edges) {
        if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.weight) {
            dist[edge.v] = -INF;
            inNegativeCycle[edge.v] = true;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (inNegativeCycle[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& edge : edges) {
            if (edge.u == u && !inNegativeCycle[edge.v]) {
                inNegativeCycle[edge.v] = true;
                q.push(edge.v);
            }
        }
    }

    for (int i = 1; i < n; ++i) {
        if (inNegativeCycle[i]) {
            cout << "-inf\n";
        } else {
            cout << dist[i] << "\n";
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    bellman_ford(n, edges);

    return 0;
}