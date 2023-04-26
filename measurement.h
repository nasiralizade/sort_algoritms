//
// Created by Nasir Alizade on 2023-04-04.
//

#include <vector>
#include <numeric>

#ifndef LABB2_V2_MEASUREMENT_H
#define LABB2_V2_MEASUREMENT_H

#endif //LABB2_V2_MEASUREMENT_H
double average_value(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    const size_t N = data.size();
    double avg = sum / N;
    return avg;
}

double std_dev(const std::vector<double>& data) {
    const size_t N = data.size();
    double avg_val = average_value(data);
    double dev_square = 0.0;
    for (double it: data) {
        dev_square += pow((it - avg_val), 2);
    }
    return std::sqrt(dev_square * (1.0 / (N - 1)));
}