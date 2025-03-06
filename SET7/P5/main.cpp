#include <bits/stdc++.h>
using namespace std;

bool isCompatible(const unordered_set<string> &a, const unordered_set<string> &b) {
  for (const auto &comp : a) {
    if (b.find(comp) == b.end())
      return false;
  }
  return true;
}

bool dfs(int v, const vector<vector<int>> &graph, vector<bool> &visited, vector<int> &matchR) {
  if (visited[v])
    return false;
  visited[v] = true;
  for (int u : graph[v]) {
    if (matchR[u] == -1 || dfs(matchR[u], graph, visited, matchR)) {
      matchR[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  
  int n, k;
  cin >> n;
  vector<unordered_set<string>> juices(n);
  string component;

  for (int i = 0; i < n; ++i) {
    cin >> k;
    for (int j = 0; j < k; ++j) {
      cin >> component;
      juices[i].insert(component);
    }
  }

  vector<vector<int>> graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && isCompatible(juices[i], juices[j])) {
        graph[i].push_back(j);
      }
    }
  }

  vector<int> matchR(n, -1);
  int matching = 0;
  for (int v = 0; v < n; ++v) {
    vector<bool> visited(n, false);
    if (dfs(v, graph, visited, matchR))
      ++matching;
  }

  cout << n - matching;

  return 0;
}