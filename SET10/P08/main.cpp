#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000179;

struct Matrix {
    int n;
    long long a[20][20];
    Matrix(int _n = 0): n(_n) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                a[i][j] = 0;
    }
    Matrix operator*(const Matrix &other) const {
        Matrix res(n);
        for(int i = 0; i < n; i++) {
            for(int k = 0; k < n; k++) {
                if (a[i][k] == 0) continue;
                long long v = a[i][k];
                for(int j = 0; j < n; j++) {
                    res.a[i][j] = (res.a[i][j] + v * other.a[k][j]) % MOD;
                }
            }
        }
        return res;
    }
    Matrix pow(long long exp) const {
        Matrix base = *this;
        Matrix result(n);
        for(int i = 0; i < n; i++) 
            result.a[i][i] = 1;\
        long long e = exp;
        while(e > 0) {
            if (e & 1LL) result = result * base;
            base = base * base;
            e >>= 1LL;
        }
        return result;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int k;
    cin >> n >> k;

    if (n == 1) {
        cout << (k % MOD) << "\n";
        return 0;
    }
    if (n == 2) {
        long long ans = (1LL * k * (k - 1)) % MOD;
        cout << ans << "\n";
        return 0;
    }

    int dim = 2 * k;
    Matrix T(dim);

    for(int r = 1; r <= k; r++) {
        int row = r - 1;
        for(int x = 1; x <= r - 1; x++) {
            int col = k + (x - 1);
            T.a[row][col] = 1;
        }
    }
    for(int r = 1; r <= k; r++) {
        int row = k + (r - 1);
        for(int x = r + 1; x <= k; x++) {
            int col = (x - 1);
            T.a[row][col] = 1;
        }
    }

    vector<long long> S2(dim, 0);
    for(int h = 1; h <= k; h++) {
        S2[h - 1]     = (h - 1);
        S2[k + h - 1] = (k - h);
    }

    Matrix Texp = T.pow(n - 2);

    vector<long long> S_n(dim, 0);
    for(int i = 0; i < dim; i++) {
        long long sum = 0;
        for(int j = 0; j < dim; j++) {
            sum = (sum + Texp.a[i][j] * S2[j]) % MOD;
        }
        S_n[i] = sum;
    }

    long long answer = 0;
    for(int i = 0; i < dim; i++) {
        answer = (answer + S_n[i]) % MOD;
    }
    cout << answer << "\n";
    return 0;
}
