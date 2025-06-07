#include "SortTester.hpp"

int main() {
        try {
        std::vector<int> sizes;
        for (int i = 500; i <= 10000; i += 100) {
            sizes.push_back(i);
        }
        SortTester::runTests(sizes);
    } catch(...) {
        std::cout << "Something went wrong;";
    }
    return 0;
}
