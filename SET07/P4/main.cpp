#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m, a, b;
char grid[MAXN][MAXN];
vector<int> g[MAXN * MAXN];
int match[MAXN * MAXN];
bool used[MAXN * MAXN];

struct Point {
    int x;
    int y;
};

bool dfs(int u) {
    if (used[u]) return false;
    used[u] = true;
    for (int v : g[u]) {
        if (match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m >> a >> b;
    vector<Point> part_a, part_b;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == '*') {
                if ((i + j) % 2 == 0) {
                    part_a.push_back({i, j});
                } else {
                    part_b.push_back({i, j});
                }
            }
        }
    }

    int free_cells = part_a.size() + part_b.size();
    if (free_cells == 0) {
        cout << "0\n";
        return 0;
    }

    if (2 * b <= a) {
        cout << free_cells * b << "\n";
        return 0;
    }

    for (size_t i = 0; i < part_a.size(); ++i) {
        Point p = part_a[i];
        for (int dir = 0; dir < 4; ++dir) {
            int nx = p.x + dx[dir];
            int ny = p.y + dy[dir];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '*') {
                auto it = find_if(part_b.begin(), part_b.end(),
                                  [nx, ny](const Point& pt) { return pt.x == nx && pt.y == ny; });
                if (it != part_b.end()) {
                    g[i].push_back(distance(part_b.begin(), it));
                }
            }
        }
    }

    memset(match, -1, sizeof(match));
    int max_matching = 0;
    for (size_t u = 0; u < part_a.size(); ++u) {
        memset(used, 0, sizeof(used));
        if (dfs(u)) {
            max_matching++;
        }
    }

    int total_cost = max_matching * a + (free_cells - 2 * max_matching) * b;
    cout << total_cost << "\n";

    return 0;
}