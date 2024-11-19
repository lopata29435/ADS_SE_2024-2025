#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

const int k = 100000;

int f(vector<int> &p, int n) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        int d = 1;
        for (int j = 0; j < i; j++)
            if (abs(i - j) == abs(p[i] - p[j]))
                d = 0;
        s += d;
    }
    return s;
}

double rnd(mt19937 &g) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(g);
}

int main() {
    int n;
    cin >> n;

    vector<int> v(n);
    iota(v.begin(), v.end(), 0);

    random_device rd;
    mt19937 g(rd());

    shuffle(v.begin(), v.end(), g);

    int ans = f(v, n);

    double t = 1;
    uniform_int_distribution<int> index_dist(0, n - 1);
    for (int i = 0; i < k && ans < n; i++) {
        t *= 0.99;
        vector<int> u = v;

        swap(u[index_dist(g)], u[index_dist(g)]);

        int val = f(u, n);
        if (val > ans || rnd(g) < exp((val - ans) / t)) {
            v = u;
            ans = val;
        }
    }

    for (int x : v)
        cout << x + 1 << " ";

    return 0;
}
