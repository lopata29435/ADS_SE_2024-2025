// StringSortTester.hpp
#ifndef STRING_SORT_TESTER_HPP
#define STRING_SORT_TESTER_HPP

#include "StringGenerator.hpp"

#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <fstream>
#include <iostream>

extern uint64_t GLOBAL_CHAR_COMPARISONS;

struct TestResult {
    std::string algName;
    int size;
    int type;
    double avgTimeMs;
    double avgCharComps;
};

class StringSortTester {
public:
    void addAlgorithm(const std::string &name,
                      std::function<void(std::vector<std::string>&)> fn)
    {
        algos_.push_back({name, fn});
    }

    void runBatch(const StringGenerator &gen,
                  const std::vector<int> &sizes,
                  const std::vector<int> &types,
                  int repetitions = 5)
    {
        results_.clear();
        using Clock = std::chrono::high_resolution_clock;

        for (auto &algo : algos_) {
            for (int type : types) {
                for (int n : sizes) {
                    auto data = gen.get(n, type);
                    double sumTime = 0;
                    double sumComps = 0;
                    for (int rep = 0; rep < repetitions; ++rep) {
                        auto v = data;
                        GLOBAL_CHAR_COMPARISONS = 0;
                        auto t0 = Clock::now();
                        algo.fn(v);
                        auto t1 = Clock::now();
                        std::chrono::duration<double, std::milli> dt = t1 - t0;
                        sumTime  += dt.count();
                        sumComps += GLOBAL_CHAR_COMPARISONS;
                    }
                    results_.push_back({
                        algo.name,
                        n,
                        type,
                        sumTime  / repetitions,
                        sumComps / repetitions
                    });
                    std::cerr << "Completed " << algo.name
                              << " n=" << n
                              << " type=" << type << "\n";
                }
            }
        }
    }

    void exportResults(const std::string &filename) const
    {
        std::ofstream out(filename);
        out << "algorithm,size,type,avgTimeMs,avgCharComps\n";
        for (auto &r : results_) {
            out << r.algName    << ","
                << r.size       << ","
                << r.type       << ","
                << r.avgTimeMs  << ","
                << r.avgCharComps
                << "\n";
        }
    }
    const std::vector<TestResult>& results() const {
        return results_;
    }

private:
    struct Algo {
        std::string name;
        std::function<void(std::vector<std::string>&)> fn;
    };
    std::vector<Algo>          algos_;
    std::vector<TestResult>    results_;
};

#endif // STRING_SORT_TESTER_HPP
