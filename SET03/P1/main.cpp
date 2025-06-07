#include <iostream>
#include <vector>

void heapify(std::vector<int>& A, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

void buildMaxHeap(std::vector<int>& A, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i);
    }
}

void heapSort(std::vector<int>& A) {
    int n = A.size();

    buildMaxHeap(A, n);

    for (int i = n - 1; i >= 1; i--) {
        std::swap(A[0], A[i]);

        heapify(A, i, 0);
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);

    for(int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    heapSort(a);

    for (int num : a) {
        std::cout << num << " ";
    }
    std::cout << '\n';

    return 0;
}
