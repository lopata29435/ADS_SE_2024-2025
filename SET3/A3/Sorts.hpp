#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

int partition(std::vector<int>& arr, int low, int high, std::mt19937& gen) {
    std::uniform_int_distribution<> dis(low, high);

    int randomPivotIndex = dis(gen);
    std::swap(arr[randomPivotIndex], arr[high]);
    int pivot = arr[high];
    int partitionIndex = low;

    for (int i = low; i < high; i++) {
        if (arr[i] < pivot) {
            std::swap(arr[i], arr[partitionIndex]);
            partitionIndex++;
        }
    }
    std::swap(arr[partitionIndex], arr[high]);
    return partitionIndex;
}

void quickSort(std::vector<int>& arr, int low, int high, std::mt19937& gen) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, gen);
        quickSort(arr, low, pivotIndex - 1, gen);
        quickSort(arr, pivotIndex + 1, high, gen);
    }
}

void QuickSort(std::vector<int>& arr, std::mt19937& gen) {
    quickSort(arr, 0, arr.size() - 1, gen);
}

void insertionSort(std::vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void heapify(std::vector<int>& arr, int n, int i, int low) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[low + left] > arr[low + largest])
        largest = left;
    if (right < n && arr[low + right] > arr[low + largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[low + i], arr[low + largest]);
        heapify(arr, n, largest, low);
    }
}

void heapSort(std::vector<int>& arr, int low, int high) {
    int n = high - low + 1;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, low);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[low], arr[low + i]);
        heapify(arr, i, 0, low);
    }
}

void introSort(std::vector<int>& arr, int low, int high, int depthLimit, std::mt19937& gen) {
    std::uniform_int_distribution<> dis(low, high);

    if (high - low < 16) {
        insertionSort(arr, low, high);
    } else if (depthLimit <= 0) {
        heapSort(arr, low, high);
    } else if (high > low) {
        int pivotIndex = low + dis(gen) % (high - low + 1);
        int pivot = arr[pivotIndex];
        std::swap(arr[pivotIndex], arr[high]);

        int partitionIndex = low;
        for (int i = low; i < high; i++) {
            if (arr[i] < pivot) {
                std::swap(arr[i], arr[partitionIndex]);
                partitionIndex++;
            }
        }
        std::swap(arr[partitionIndex], arr[high]);

        introSort(arr, low, partitionIndex - 1, depthLimit - 1, gen);
        introSort(arr, partitionIndex + 1, high, depthLimit - 1, gen);
    }
}

void Introsort(std::vector<int>& arr, std::mt19937& gen) {
    int n = arr.size();
    int depthLimit = 2 * std::log2(n);
    introSort(arr, 0, n - 1, depthLimit, gen);
}