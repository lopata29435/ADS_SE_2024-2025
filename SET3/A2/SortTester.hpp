#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "ArrayGenerator.hpp"
#include "Sorts.hpp"

class SortTester {
public:
    template<typename SortFunction>
    static long long testSort(SortFunction sortFunction, std::vector<int> arr) {
        auto start = std::chrono::high_resolution_clock::now();
        sortFunction(arr);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    static void runTests(std::vector<int> thresholds, std::vector<int> sizes) {
        ArrayGenerator generator;

        // Для каждой комбинации Threshold, Type, и SortMethod создаем отдельный файл
        for(int threshold: thresholds) {
            for (int size : sizes) {
                std::vector<int> randomArr = generator.generateRandomArray(size, 0, 6000);
                std::vector<int> reversedArr = generator.generateReversedArray(size);
                std::vector<int> nearlySortedArr = generator.generateNearlySortedArray(size, size / 10);

                // Для каждого типа массива и сортировки создаем файл
                std::vector<std::string> arrayTypes = {"Random", "Reversed", "NearlySorted"};
                std::vector<std::string> sortMethods = {"MergeSort", "HybridSort"};
                
                // Проходим по каждому типу массива и сортировки
                for (const auto& arrayType : arrayTypes) {
                    for (const auto& sortMethod : sortMethods) {
                        std::ostringstream fileName;
                        fileName << "sort_results_" << arrayType << "_" << sortMethod << "_Threshold" << threshold << ".csv";

                        std::ofstream outFile(fileName.str(), std::ios::app); // Открываем файл в режиме добавления
                        if (!outFile.is_open()) {
                            std::cerr << "Failed to open file for writing: " << fileName.str() << "\n";
                            return;
                        }

                        // Если файл пустой, записываем заголовок
                        if (outFile.tellp() == 0) {
                            outFile << "Size,TimeMicroseconds,Threshold\n";
                        }

                        long long time = 0;

                        // Тестируем разные массивы
                        if (arrayType == "Random") {
                            if (sortMethod == "MergeSort") {
                                time = testSort([&](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, randomArr);
                            } else if (sortMethod == "HybridSort") {
                                time = testSort([&](std::vector<int>& arr) { hybridMergeSort(arr, 0, arr.size() - 1, threshold); }, randomArr);
                            }
                        } else if (arrayType == "Reversed") {
                            if (sortMethod == "MergeSort") {
                                time = testSort([&](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, reversedArr);
                            } else if (sortMethod == "HybridSort") {
                                time = testSort([&](std::vector<int>& arr) { hybridMergeSort(arr, 0, arr.size() - 1, threshold); }, reversedArr);
                            }
                        } else if (arrayType == "NearlySorted") {
                            if (sortMethod == "MergeSort") {
                                time = testSort([&](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, nearlySortedArr);
                            } else if (sortMethod == "HybridSort") {
                                time = testSort([&](std::vector<int>& arr) { hybridMergeSort(arr, 0, arr.size() - 1, threshold); }, nearlySortedArr);
                            }
                        }

                        // Записываем результаты в файл
                        outFile << size << "," << time << "," << threshold << "\n";
                    }
                }
            }
        }
        std::cout << "Results written to respective CSV files.\n";
    }
};
