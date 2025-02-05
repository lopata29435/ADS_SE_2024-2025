#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int p1 = 1000003;
const int p2 = 1000033;
const int p3 = 1000037;
const int p4 = 1000039;

struct HashPair {
    int h1, h2;
    HashPair(int a = 0, int b = 0) : h1(a), h2(b) {}

    bool operator==(const HashPair& other) const {
        return h1 == other.h1 && h2 == other.h2;
    }
};


namespace std {
    template<>
    struct hash<HashPair> {
        size_t operator()(const HashPair& hp) const {
            return hash<int>()(hp.h1) ^ (hash<int>()(hp.h2) << 1);
        }
    };
}

bool check_anagram(const vector<int>& a, int a_start, const vector<int>& b, int b_start, int k) {
    vector<int> sub_a(a.begin() + a_start, a.begin() + a_start + k);
    vector<int> sub_b(b.begin() + b_start, b.begin() + b_start + k);
    sort(sub_a.begin(), sub_a.end());
    sort(sub_b.begin(), sub_b.end());
    return sub_a == sub_b;
}

pair<int, int> check(int k, const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    int m = b.size();

    if (k <= 0 || k > n || k > m) return {-1, -1};

    unordered_map<HashPair, int> hash_a;
    unordered_map<int, int> freq;
    HashPair current(0, 0);

    for (int i = 0; i < k; ++i) freq[a[i]]++;
    for (const auto& pr : freq) {
        current.h1 += pr.first * p1 + pr.second * p2;
        current.h2 += pr.first * p3 + pr.second * p4;
    }
    hash_a[current] = 0;

    for (int i = 1; i <= n - k; ++i) {
        int left = a[i - 1];
        int right = a[i + k - 1];

        auto it = freq.find(left);
        current.h1 -= left * p1 + it->second * p2;
        current.h2 -= left * p3 + it->second * p4;

        if (--(it->second) == 0) freq.erase(it);
        else {
            current.h1 += left * p1 + freq[left] * p2;
            current.h2 += left * p3 + freq[left] * p4;
        }

        it = freq.find(right);
        if (it != freq.end()) {
            current.h1 -= right * p1 + it->second * p2;
            current.h2 -= right * p3 + it->second * p4;
            ++(it->second);
            current.h1 += right * p1 + it->second * p2;
            current.h2 += right * p3 + it->second * p4;
        } else {
            freq[right] = 1;
            current.h1 += right * p1 + p2;
            current.h2 += right * p3 + p4;
        }

        if (hash_a.find(current) == hash_a.end()) hash_a[current] = i;
    }

    freq.clear();
    current.h1 = current.h2 = 0;
    for (int i = 0; i < k; ++i) freq[b[i]]++;
    for (const auto& pr : freq) {
        current.h1 += pr.first * p1 + pr.second * p2;
        current.h2 += pr.first * p3 + pr.second * p4;
    }

    if (hash_a.find(current) != hash_a.end()) {
        if (check_anagram(a, hash_a[current], b, 0, k))
            return {hash_a[current], 0};
    }

    for (int i = 1; i <= m - k; ++i) {
        int left = b[i - 1];
        int right = b[i + k - 1];
        
        auto it = freq.find(left);
        current.h1 -= left * p1 + it->second * p2;
        current.h2 -= left * p3 + it->second * p4;

        if (--(it->second) == 0) freq.erase(it);
        else {
            current.h1 += left * p1 + freq[left] * p2;
            current.h2 += left * p3 + freq[left] * p4;
        }

        it = freq.find(right);
        if (it != freq.end()) {
            current.h1 -= right * p1 + it->second * p2;
            current.h2 -= right * p3 + it->second * p4;
            ++(it->second);
            current.h1 += right * p1 + it->second * p2;
            current.h2 += right * p3 + it->second * p4;
        } else {
            freq[right] = 1;
            current.h1 += right * p1 + p2;
            current.h2 += right * p3 + p4;
        }

        if (hash_a.find(current) != hash_a.end()) {
            if (check_anagram(a, hash_a[current], b, i, k))
                return {hash_a[current], i};
        }
    }
    
    return {-1, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) cin >> b[i];

    int lo = 1, hi = min(n, m);
    int best_k = 0, best_i = -1, best_j = -1;
    
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        pair<int, int> candidate = check(mid, a, b);
        
        if (candidate.first != -1) {
            best_k = mid;
            best_i = candidate.first;
            best_j = candidate.second;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    if (best_k == 0) 
        cout << "0 -1 -1\n";
    else 
        cout << best_k << " " << best_i + 1 << " " << best_j + 1 << "\n";

    return 0;
}