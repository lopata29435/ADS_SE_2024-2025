#include <vector>
#include <algorithm>
#include <random>

class ArrayGenerator {
public:
    static std::vector<int> generateRandomArray(int size, int minValue, int maxValue) {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minValue, maxValue);
        std::generate(arr.begin(), arr.end(), [&]() { return dis(gen); });
        return arr;
    }

    static std::vector<int> generateReversedArray(int size) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = size - i;
        }
        return arr;
    }

    static std::vector<int> generateNearlySortedArray(int size, int swaps) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = i;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = 0; i < swaps; ++i) {
            int idx1 = gen() % size;
            int idx2 = gen() % size;
            std::swap(arr[idx1], arr[idx2]);
        }
        return arr;
    }
};