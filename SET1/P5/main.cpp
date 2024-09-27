#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::deque<int> first;
    std::deque<int> second;

    int t, x;
    char c;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cin >> c;

        if (c == '+') {
            std::cin >> x;
            second.push_back(x);
        }
        if (c == '*') {
            std::cin >> x;
            if ((first.size() + second.size()) % 2) {
                second.push_front(x);
            } else {
                first.push_back(x);
            }
        }
        if (c == '-') {
            std::cout << first.front() << '\n';
            first.pop_front();
        }
        while (first.size() < second.size()) {
            first.push_back(second.front());
            second.pop_front();
        }
    }
}
