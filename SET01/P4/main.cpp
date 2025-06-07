#include <iostream>
#include <stack>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> train(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> train[i];
    }
    
    std::stack<int> depot;
    std::vector<std::pair<int, int>> actions;
    int expected = 1;
    
    for (int i = 0; i < n; ++i) {
        depot.push(train[i]);
        actions.push_back({1, 1});
        
        while (!depot.empty() && depot.top() == expected) {
            depot.pop();
            actions.push_back({2, 1});
            expected++;
        }
    }
    
    if (expected == n + 1) {
        for (auto action : actions) {
            std::cout << action.first << " " << action.second << '\n';
        }
    } else {
        std::cout << 0 << '\n';
    }
    
    return 0;
}