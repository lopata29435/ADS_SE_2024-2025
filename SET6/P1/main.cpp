#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> rg;
vector<bool> used;
stack<int> order;
vector<int> components;

void dfs1(int v) {
    used[v] = 1;
    for(int next : g[v]) {
        if(!used[next]) {
            dfs1(next);
        }
    }
    order.push(v);
}

void dfs2(int v, int label) {
    used[v] = 1;
    components[v] = label;
    for(int next : rg[v]) {
        if(!used[next]) {
            dfs2(next, label);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    g.assign(n, vector<int>());
    rg.assign(n, vector<int>());
    used.assign(n, false);
    components.assign(n, -1);

    int x, y;
    for(int i = 0; i < m; ++i) {
        cin >> x >> y;
        x--, y--;
        g[x].push_back(y);
        rg[y].push_back(x);
    }

    for(int i = 0; i < n; ++i) {
        if(!used[i]) {
            dfs1(i);
        }
    }

    fill(used.begin(), used.end(), false);
    int label = 0;
    while (!order.empty()) {
        int v = order.top();
        order.pop();
        if (!used[v]) {
            dfs2(v, ++label);
        }
    }

    cout << label << '\n';
    for(int it: components) {
        cout << it << ' ';
    }

    return 0;
}