#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int TESTS = 9;
const int MAX_ACTIONS = 500000;
const int POP_SIZE = 50;
const int GENERATIONS = 3000;
const double MUTATION_RATE = 0.15;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct EngineMatrix {
    vector<vector<int>> grid;
    ll score = 0;
    vector<tuple<int, int, int>> actions;
};

bool can_place(const vector<vector<int>>& grid, int n, int m, int x, int y, int typ) {
    if (typ == 0) return true;
    vector<bool> need(typ, false);
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
            int t = grid[nx][ny];
            if (t >= 0 && t < typ) need[t] = true;
        }
    }
    return all_of(need.begin(), need.end(), [](bool b) { return b; });
}

EngineMatrix generate_candidate(int n, int m, const vector<ll>& p, ll wmax) {
    EngineMatrix em;
    em.grid.assign(n, vector<int>(m, -1));
    em.actions.clear();
    ll curW = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            em.grid[i][j] = 0;
            em.actions.emplace_back(i + 1, j + 1, 0);
            curW += p[0];
        }

    bool updated = true;
    while (updated && em.actions.size() < MAX_ACTIONS && curW < wmax) {
        updated = false;
        vector<tuple<ll, int, int, int>> upgrades;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int cur = em.grid[i][j];
                for (int t = 4; t > cur; t--) {
                    if (can_place(em.grid, n, m, i, j, t)) {
                        ll gain = p[t] - p[cur];
                        if (curW + gain <= wmax)
                            upgrades.emplace_back(gain, i, j, t);
                    }
                }
            }
        }
        shuffle(upgrades.begin(), upgrades.end(), rng);
        for (auto& [gain, i, j, t] : upgrades) {
            if (em.grid[i][j] < t && can_place(em.grid, n, m, i, j, t)) {
                curW += p[t] - p[em.grid[i][j]];
                em.grid[i][j] = t;
                em.actions.emplace_back(i + 1, j + 1, t);
                updated = true;
                if (curW >= wmax || em.actions.size() >= MAX_ACTIONS) break;
            }
        }
    }
    em.score = curW;
    return em;
}

void mutate(EngineMatrix& em, const vector<ll>& p, int n, int m, ll wmax) {
    int x = rng() % n, y = rng() % m;
    int cur = em.grid[x][y];
    int new_t = rng() % 5;
    if (new_t != cur && can_place(em.grid, n, m, x, y, new_t)) {
        ll delta = p[new_t] - p[cur];
        if (em.score + delta <= wmax) {
            em.grid[x][y] = new_t;
            em.score += delta;
            em.actions.emplace_back(x + 1, y + 1, new_t);
        }
    }
}

EngineMatrix crossover(const EngineMatrix& a, const EngineMatrix& b, const vector<ll>& p, int n, int m, ll wmax) {
    EngineMatrix child;
    child.grid.assign(n, vector<int>(m, -1));
    child.actions.clear();
    ll total = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int from = rng() % 2;
            int t = (from == 0 ? a.grid[i][j] : b.grid[i][j]);
            if (t == 0 || can_place(child.grid, n, m, i, j, t)) {
                child.grid[i][j] = t;
                child.actions.emplace_back(i + 1, j + 1, t);
                total += p[t];
            } else {
                child.grid[i][j] = 0;
                child.actions.emplace_back(i + 1, j + 1, 0);
                total += p[0];
            }
        }
    child.score = total;
    return child;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int test = 1; test <= TESTS; ++test) {
        char fname[10];
        sprintf(fname, "%02d", test);
        ifstream fin(fname);
        sprintf(fname, "%02d.out", test);
        ofstream fout(fname);


        int t, n, m;
        ll wmax;
        fin >> t >> n >> m >> wmax;
        vector<ll> p(5);
        for (ll& x : p) fin >> x;

        vector<EngineMatrix> population;
        for (int i = 0; i < POP_SIZE; ++i) {
            population.push_back(generate_candidate(n, m, p, wmax));
        }

        for (int gen = 0; gen < GENERATIONS; ++gen) {
            sort(population.begin(), population.end(), [](auto& a, auto& b) {
                return a.score > b.score;
            });
            while ((int)population.size() > POP_SIZE) population.pop_back();
            while ((int)population.size() < POP_SIZE) {
                int i = rng() % (POP_SIZE / 2), j = rng() % (POP_SIZE / 2);
                EngineMatrix child = crossover(population[i], population[j], p, n, m, wmax);
                if (rng() % 100 < (MUTATION_RATE * 100)) mutate(child, p, n, m, wmax);
                population.push_back(child);
            }
        }

        sort(population.begin(), population.end(), [](auto& a, auto& b) {
            return a.score > b.score;
        });
        auto& best = population[0];

        fout << best.score << " " << best.actions.size() << "\n";
        for (auto& [x, y, t] : best.actions)
            fout << x << " " << y << " " << t << "\n";
    }
    return 0;
}
