#include "stringGenerator.hpp"
#include "stringSortTester.hpp"
#include "sortingAlgorithms.hpp"

#include <cstdint>
#include <iostream>

uint64_t GLOBAL_CHAR_COMPARISONS = 0;

int main() {
    StringGenerator gen(12345);
    gen.generateBase(3000 , 10, 200);
    gen.setNearlySortedSwaps(150);

    StringSortTester tester;
    tester.addAlgorithm("mergesort_lcp",    alg_string_mergesort_lcp);
    tester.addAlgorithm("quick3way",        alg_string_quick3way);
    tester.addAlgorithm("msd_radix",        alg_msd_radix);
    tester.addAlgorithm("msd_radix_switch", alg_msd_radix_switch);

    std::vector<int> sizes;
    for (int n = 100; n <= 3000; n += 100)
        sizes.push_back(n);
    std::vector<int> types = { 0, 1, 2 }; // 0=random,1=reverse,2=nearly

    tester.runBatch(gen, sizes, types, 5);

    tester.exportResults("results.csv");

    std::cout << "Done!\n";
    return 0;
}