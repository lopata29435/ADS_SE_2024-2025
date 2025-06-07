#include <iostream>
#include <vector>

#define int long long

int crossover;

void multiply(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void split(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, int row, int col, int n) {
    for (int i1 = 0, i2 = row; i1 < n; i1++, i2++) {
        for (int j1 = 0, j2 = col; j1 < n; j1++, j2++) {
            B[i1][j1] = A[i2][j2];
        }
    }
}

void join(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, int row, int col, int n) {
    for (int i1 = 0, i2 = row; i1 < n; i1++, i2++) {
        for (int j1 = 0, j2 = col; j1 < n; j1++, j2++) {
            B[i2][j2] = A[i1][j1];
        }
    }
}

void add(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C, int n) {
    if (n % 2 != 0) {
        n++;
        A.resize(n);
        B.resize(n);
        C.resize(n);
        for (int i = 0; i < n; i++) {
            A[i].resize(n);
            B[i].resize(n);
            C[i].resize(n);
        }
    }

    if (n <= crossover) {
        multiply(A, B, C, n);
        return;
    } else {
        int new_n = n / 2;
        std::vector<int> inner(new_n);

        std::vector<std::vector<int>> A11(new_n, inner), A12(new_n, inner), A21(new_n, inner), A22(new_n, inner);
        std::vector<std::vector<int>> B11(new_n, inner), B12(new_n, inner), B21(new_n, inner), B22(new_n, inner);
        std::vector<std::vector<int>> C11(new_n, inner), C12(new_n, inner), C21(new_n, inner), C22(new_n, inner);

        split(A, A11, 0, 0, new_n);
        split(A, A12, 0, new_n, new_n);
        split(A, A21, new_n, 0, new_n);
        split(A, A22, new_n, new_n, new_n);
        split(B, B11, 0, 0, new_n);
        split(B, B12, 0, new_n, new_n);
        split(B, B21, new_n, 0, new_n);
        split(B, B22, new_n, new_n, new_n);

        std::vector<std::vector<int>> M1(new_n, inner), M2(new_n, inner), M3(new_n, inner);
        std::vector<std::vector<int>> M4(new_n, inner), M5(new_n, inner), M6(new_n, inner), M7(new_n, inner);
        std::vector<std::vector<int>> result1(new_n, inner), result2(new_n, inner);


        add(A11, A22, result1, new_n);
        add(B11, B22, result2, new_n);
        strassen(result1, result2, M1, new_n);

        add(A21, A22, result1, new_n);
        strassen(result1, B11, M2, new_n);

        subtract(B12, B22, result2, new_n);
        strassen(A11, result2, M3, new_n);

        subtract(B21, B11, result2, new_n);
        strassen(A22, result2, M4, new_n);

        add(A11, A12, result1, new_n);
        strassen(result1, B22, M5, new_n);

        subtract(A21, A11, result1, new_n);
        add(B11, B12, result2, new_n);
        strassen(result1, result2, M6, new_n);

        subtract(A12, A22, result1, new_n);
        add(B21, B22, result2, new_n);
        strassen(result1, result2, M7, new_n);

        add(M1, M4, result1, new_n);
        subtract(result1, M5, result2, new_n);
        add(result2, M7, C11, new_n);

        add(M3, M5, C12, new_n);
        add(M2, M4, C21, new_n);

        add(M1, M3, result1, new_n);
        subtract(result1, M2, result2, new_n);
        add(result2, M6, C22, new_n);

        join(C11, C, 0, 0, new_n);
        join(C12, C, 0, new_n, new_n);
        join(C21, C, new_n, 0, new_n);
        join(C22, C, new_n, new_n, new_n);
    }
}


signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    crossover = 300;
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    std::vector<std::vector<int>> b(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> b[i][j];
        }
    }
    std::vector<std::vector<int>> c(n, std::vector<int>(n));
    strassen(a, b, c, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << c[i][j] << ' ';
        }
        std::cout << '\n';
    }
   return 0;
}