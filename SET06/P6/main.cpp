#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <algorithm>

using namespace std;

int sumDigits(int y) {
    int sum = 0;
    while (y > 0) {
        sum += y % 10;
        y /= 10;
    }
    return sum;
}

void findMinCost(int n, int a, int b) {
    vector<vector<pair<int, int>>> graph(n + 1);

    for (int x = 1; x <= n; ++x) {
        string s = to_string(x);
        for (size_t i = 0; i < s.length(); ++i) {
            for (size_t j = i + 1; j <= s.length(); ++j) {
                string yStr = s.substr(i, j - i);
                int y = stoi(yStr);
                if (y == 0) continue;
                if (x + y <= n) {
                    graph[x].push_back({x + y, sumDigits(y)});
                }
                if (x - y >= 1) {
                    graph[x].push_back({x - y, sumDigits(y)});
                }
            }
        }
    }

    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    dist[a] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, a});

    while (!pq.empty()) {
        int u = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        if (currentDist > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[b] == INT_MAX) {
        cout << -1 << endl;
        return;
    }

    vector<int> path;
    for (int v = b; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << dist[b] << endl;

    cout << path.size() - 1 << endl;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        int diff = path[i + 1] - path[i];
        if (diff > 0) {
            cout << "+" << diff << endl;
        } else {
            cout << diff << endl;
        }
    }
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    findMinCost(n, a, b);

    return 0;
}