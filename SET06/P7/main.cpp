#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100010;
const int MAXM = 300010;

vector<vector<int>> adj;
vector<vector<int>> adj_rev;
vector<bool> visited;
vector<int> component;
stack<int> order;

void dfs1(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs1(u);
        }
    }
    order.push(v);
}

void dfs2(int v, int c) {
    component[v] = c;
    for (int u : adj_rev[v]) {
        if (component[u] == -1) {
            dfs2(u, c);
        }
    }
}

bool solve2SAT(int n, vector<pair<int, int>>& clauses) {
    adj.assign(2 * n, vector<int>());
    adj_rev.assign(2 * n, vector<int>());
    visited.assign(2 * n, false);
    component.assign(2 * n, -1);

    for (auto& clause : clauses) {
        int x = clause.first;
        int y = clause.second;
        adj[x ^ 1].push_back(y);
        adj[y ^ 1].push_back(x);
        adj_rev[y].push_back(x ^ 1);
        adj_rev[x].push_back(y ^ 1);
    }

    for (int i = 0; i < 2 * n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    int c = 0;
    while (!order.empty()) {
        int v = order.top();
        order.pop();
        if (component[v] == -1) {
            dfs2(v, c++);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (component[2 * i] == component[2 * i + 1]) {
            return false;
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        vector<pair<int, int>> clauses;
        for (int i = 0; i < m; ++i) {
            int i1, e1, i2, e2;
            cin >> i1 >> e1 >> i2 >> e2;
            int x = 2 * i1 + (e1 ^ 1);
            int y = 2 * i2 + (e2 ^ 1);
            clauses.emplace_back(x, y);
        }

        if (solve2SAT(n, clauses)) {
            for (int i = 0; i < n; ++i) {
                cout << (component[2 * i] > component[2 * i + 1] ? 1 : 0);
            }
            cout << '\n';
        }
    }

    return 0;
}