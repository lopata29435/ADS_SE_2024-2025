#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "ArrayGenerator.hpp"
#include "Sorts.hpp"

class SortTester {
public:
    static void writeHeaderIfNeeded(const std::string& fileName) {
        std::ifstream inFile(fileName);
        if (!inFile.is_open() || inFile.peek() == EOF) {
            std::ofstream outFile(fileName, std::ios::trunc);
            if (!outFile.is_open()) {
                std::cerr << "Failed to open file for writing header: " << fileName << "\n";
                return;
            }
            outFile << "Size,TimeMicroseconds\n";
        }
    }

    template<typename SortFunction>
    static long long testSort(SortFunction sortFunction, std::vector<int> arr) {
        auto start = std::chrono::high_resolution_clock::now();
        sortFunction(arr);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    static void runTests(std::vector<int> sizes) {
        ArrayGenerator generator;
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int size : sizes) {
                std::vector<int> randomArr = generator.generateRandomArray(size, 0, 6000);
                std::vector<int> reversedArr = generator.generateReversedArray(size);
                std::vector<int> nearlySortedArr = generator.generateNearlySortedArray(size, size / 10);

                std::vector<std::string> arrayTypes = {"Random", "Reversed", "NearlySorted"};
                std::vector<std::string> sortMethods = {"Introsort", "QuickSort"};

                for (const auto& arrayType : arrayTypes) {
                    for (const auto& sortMethod : sortMethods) {
                        std::ostringstream fileName;
                        fileName << "sort_results_" << arrayType << "_" << sortMethod << ".csv";

                        writeHeaderIfNeeded(fileName.str());

                        std::ofstream outFile(fileName.str(), std::ios::app);
                        if (!outFile.is_open()) {
                            std::cerr << "Failed to open file for writing: " << fileName.str() << "\n";
                            return;
                        }

                        long long time = 0;

                        if (arrayType == "Random") {
                            if (sortMethod == "Introsort") {
                                time = testSort([&](std::vector<int>& arr) { Introsort(arr, gen); }, randomArr);
                            } else if (sortMethod == "QuickSort") {
                                time = testSort([&](std::vector<int>& arr) { QuickSort(arr, gen); }, randomArr);
                            }
                        } else if (arrayType == "Reversed") {
                            if (sortMethod == "Introsort") {
                                time = testSort([&](std::vector<int>& arr) { Introsort(arr, gen); }, reversedArr);
                            } else if (sortMethod == "QuickSort") {
                                time = testSort([&](std::vector<int>& arr) { QuickSort(arr, gen); }, reversedArr);
                            }
                        } else if (arrayType == "NearlySorted") {
                            if (sortMethod == "Introsort") {
                                time = testSort([&](std::vector<int>& arr) { Introsort(arr, gen); }, nearlySortedArr);
                            } else if (sortMethod == "QuickSort") {
                                time = testSort([&](std::vector<int>& arr) { QuickSort(arr, gen); }, nearlySortedArr);
                            }
                        }

                        outFile << size << "," << time << "\n";
                    }
                }
            }
        std::cout << "Results written to respective CSV files.\n";
    }
};
