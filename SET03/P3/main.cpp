#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>

using namespace std;


void radixSort(vector<int32_t>& arr) {
    const int32_t base = 256;
    vector<queue<int32_t>> buckets(base);

    for (int32_t shift = 0; shift < 32; shift += 8) {
        for (int32_t num : arr) {
            int32_t byte = (num >> shift) & 0xFF;
            buckets[byte].push(num);
        }

        int32_t index = 0;
        for (int32_t i = 0; i < base; ++i) {
            while (!buckets[i].empty()) {
                arr[index++] = buckets[i].front();
                buckets[i].pop();
            }
        }
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int32_t n;
    std::cin >> n;
    std::vector<int32_t> pos;
    std::vector<int32_t> neg;

    int32_t x;
    for (int32_t i = 0; i < n; i++) {
        std::cin >> x;
        if(x >= 0) {
            pos.push_back(x);
        } else {
            neg.push_back(-x);
        }
    }

    radixSort(pos);
    radixSort(neg);

    
    reverse(neg.begin(), neg.end());
    for (int32_t i = 0; i < neg.size(); i++) {
        std::cout << -neg[i] << " ";
    } 
    for (int32_t i = 0; i < pos.size(); i++) {
        std::cout << pos[i] << " ";
    } 
    

    return 0;
}
