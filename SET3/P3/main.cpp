#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& A, int n, int exp) {
    std::vector<int> output(n);
    std::vector<int> count(512, 0);

    for (int i = 0; i < n; i++) {
        int idx = (A[i] / exp) % 256 + 256;
        count[idx]++;
    }

    for (int i = 1; i < 512; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int idx = (A[i] / exp) % 256 + 256;
        output[count[idx] - 1] = A[i];
        count[idx]--;
    }

    for (int i = 0; i < n; i++) {
        A[i] = output[i];
    }
}

void radixSort(std::vector<int>& A, int n) {
    int maxVal = *std::max_element(A.begin(), A.end());
    int minVal = *std::min_element(A.begin(), A.end());

    for (int exp = 1; maxVal / exp > 0 || minVal / exp < 0; exp *= 256) {
        countingSort(A, n, exp);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    radixSort(a, n);

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }

    return 0;
}
