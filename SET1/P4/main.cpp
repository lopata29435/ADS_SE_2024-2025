#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> train(n);
    for (int i = 0; i < n; ++i) {
        cin >> train[i];
    }
    
    stack<int> depot;
    vector<pair<int, int>> actions;
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
            cout << action.first << " " << action.second << '\n';
        }
    } else {
        cout << 0 << '\n';
    }
    
    return 0;
}