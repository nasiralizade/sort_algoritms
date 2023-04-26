//
// Created by Nasir Alizade on 2023-04-20.
//

#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <functional>
#include "generate.h"
#include "measurement.h"


#ifndef LABB2_V2_TAKE_TIME_H
#define LABB2_V2_TAKE_TIME_H

#endif //LABB2_V2_TAKE_TIME_H
template<typename SortFunction>
double take_time(SortFunction sort, std::vector<int> &data) {
    int num_runs = 5;
    double total_time = 0.0;
    for (int i = 0; i < num_runs; ++i) {
        auto start = std::chrono::steady_clock::now();
        sort(data.begin(), data.end());
        auto stop = std::chrono::steady_clock::now();
        total_time += std::chrono::duration<double, std::milli>(stop - start).count();
    }
    return total_time / num_runs;
}

void run_sort(const int choice, int SIZE, int REPETITIONS, int SAMPLES) {


    const std::vector<std::string> files = {"random.txt", "constant.txt", "increase.txt", "decrease.txt"};
    const std::vector<std::string> sorts = {"std_sort", "quicksort", "quicksortMFT", "insertion_sort", "selectionSort"};
    std::vector<bool> check;
    std::string line(90, '-');
    std::cout << "Running " << sorts[choice - 1] << "...\n\n";
    std::cout << "File\t\tN\t\tT[ms]\t\tdev[ms]\t\tSamples\n";
    std::cout << line << "\n";

    for (const auto &file: files) {
        std::ofstream os(file, std::ios::app);
        if (!os.is_open()) {
            std::cerr << "Failed to open file " << file << std::endl;
            return;
        }

        os << sorts[choice - 1] << "\n";
        os << "N\t\tT[ms]\t\tdev[ms]\t\tSamples\n";

        for (int iter = 0; iter < REPETITIONS; ++iter) {
            int increment = iter + 1;
            std::vector<int> data(SIZE * increment);
            if (file == "random.txt") {
                generate_random(data);
            } else if (file == "constant.txt") {
                generate_constant(data);
            } else if (file == "increase.txt") {
                generate_increasing(data);
            } else if (file == "decrease.txt") {
                generate_decreasing(data);
            }
            std::vector<double> period(SAMPLES);
            for (int i = 0; i < SAMPLES; ++i) {
                std::vector<int> copy = data;
                if (choice == 1) {
                    period[i] = take_time(standardsort, copy);
                } else if (choice == 2) {
                    period[i] = take_time(quicksort, copy);
                } else if (choice == 3) {
                    period[i] = take_time(quicksort2, copy);
                } else if (choice == 4) {
                    period[i] = take_time(insertion_sort, copy);
                } else if (choice == 5) {
                    period[i] = take_time(selectionSort, copy);
                }
                auto check_value = std::is_sorted(copy.begin(), copy.end());
                check.push_back(check_value);
            }
            auto find_false_value = std::find(check.begin(), check.end(), false);
            if (find_false_value != check.end()) {
                std::cerr << "not sorted\t";
            } else {
                std::cout << "sorted\t";
            }
            os << SIZE * increment << "\t" << average_value(period) << "\t" << std_dev(period) << "\t" << SAMPLES
               << '\n';
            std::cout << file << "\t" << SIZE * increment << "\t" << average_value(period) << "\t\t"
                      << std_dev(period) << "\t" << SAMPLES << '\n';
        }

        os.close();
        std::cout << line << "\n\n";
    }
}
