#include <bits/stdc++.h>
using namespace std;

int n, m, c;
int grid_[10][10];
bool done = false;

struct R { int x1, x2, y1, y2; };
vector<R> rects;
vector<int> rIdx[10][10];

inline bool all_equal(int a, int b, int c, int d) {
    return a == b && a == c && a == d;
}

int bad() {
    int cnt = 0;
    for (auto &r : rects) {
        int col = grid_[r.x1][r.y1];
        if (all_equal(col, grid_[r.x1][r.y2], grid_[r.x2][r.y1], grid_[r.x2][r.y2])) {
            cnt++;
        }
    }
    return cnt;
}

int delta(int x, int y, int oldCol, int newCol) {
    int d = 0;
    for (int i : rIdx[x][y]) {
        auto &r = rects[i];
        int c1 = grid_[r.x1][r.y1];
        int c2 = grid_[r.x1][r.y2];
        int c3 = grid_[r.x2][r.y1];
        int c4 = grid_[r.x2][r.y2];
        bool was = all_equal(c1, c2, c3, c4);
        
        if (r.x1 == x && r.y1 == y) c1 = newCol;
        if (r.x1 == x && r.y2 == y) c2 = newCol;
        if (r.x2 == x && r.y1 == y) c3 = newCol;
        if (r.x2 == x && r.y2 == y) c4 = newCol;

        bool now = all_equal(c1, c2, c3, c4);
        d += now - was;\
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> c;

    rects.clear();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            rIdx[i][j].clear();

    for (int x1 = 0; x1 < n; ++x1)
        for (int x2 = x1 + 1; x2 < n; ++x2)
            for (int y1 = 0; y1 < m; ++y1)
                for (int y2 = y1 + 1; y2 < m; ++y2) {
                    int id = (int)rects.size();
                    rects.push_back({x1, x2, y1, y2});
                    rIdx[x1][y1].push_back(id);
                    rIdx[x1][y2].push_back(id);
                    rIdx[x2][y1].push_back(id);
                    rIdx[x2][y2].push_back(id);
                }

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> colorDist(1, c);
    uniform_real_distribution<double> realDist(0.0, 1.0);

    while (!done) {
        auto T0 = chrono::steady_clock::now();
        auto T1 = T0 + chrono::milliseconds(100);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid_[i][j] = colorDist(rng);

        int p = bad();
        if (p == 0) break;

        double temp = 1.0, cool = 0.996;
        int iter = 0;
        while (chrono::steady_clock::now() < T1 && !done) {
            ++iter;
            int x = rng() % n;
            int y = rng() % m;
            int oc = grid_[x][y];
            int nc = (oc + (rng() % (c - 1)) + 1);
            if (nc > c) nc -= c;

            int d = delta(x, y, oc, nc);

            double r = realDist(rng);
            if (d <= 0 || (-d / temp) > log(r)) {
                grid_[x][y] = nc;
                p += d;
                if (p == 0) {
                    done = true;
                    break;
                }
            }
            temp *= cool;

            if (iter % 1000 == 0) {
                if (chrono::steady_clock::now() >= T1) break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << grid_[i][j] << (j + 1 < m ? ' ' : '\n');
    }
    return 0;
}
