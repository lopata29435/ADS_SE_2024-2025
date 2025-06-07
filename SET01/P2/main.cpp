#include <iostream>
#include <vector>
#include <set>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    
    
    int mx = -1;
    int cnt = 0;
    
    std::set<std::vector<int>> uniq;

    for (int s = 0; s < n; ++s) {
        std::vector<int> sa(n);
        
        for (int i = 0; i < n; ++i) {
            sa[i] = a[(i + s) % n];
        }

        if(uniq.find(sa) != uniq.end()) {
            continue;
        }
        uniq.insert(sa);

        int dst = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] != sa[i]) {
                ++dst;
            }
        }
        
        if (dst > mx) {
            mx = dst;
            cnt = 1;
        } else if (dst == mx) {
            ++cnt;
        }
    }
    
    std::cout << cnt << '\n';

    return 0;
}