#ifndef SORT_H
#define SORT_H

#include "generate.h"


//Selection sort
template<typename Iterator>
void selection_sort(Iterator first, Iterator last) {
    for (Iterator i = first; i !=last-1 ; ++i) {
        Iterator min=i;
        for (Iterator j = i+1; j !=last ; ++j) {
            if (*j<*min){
                min=j;
            }
        }
        if (min!=i){
            std::swap(*i,*min);
        }
    }
}

//Insertion sort
template<typename Iterator>
void insertion_sort(Iterator first, Iterator last) {
    for (auto i = first + 1; i != last; i++) {
        Iterator j = i;
        while (j > first && *(j - 1) > *j) {
            std::swap(*j, *(j - 1));
            j = j - 1;
        }
    }
}


// median_quick_sort
template<typename Iterator>
Iterator median_of_three(Iterator first, Iterator last) {
    Iterator mid = first + (last - first) / 2;
    if (*first > *mid) {
        std::swap(*first, *mid);
    }
    if (*first > *last) {
        std::swap(*first, *last);
    }
    if (*mid > *last) {
        std::swap(*mid, *last);
    }
    return mid;
}

template<typename Iterator>
Iterator partition3(Iterator first, Iterator last) {
    auto pivot = median_of_three(first, last);
    int pivot_value = *pivot;
    Iterator i = first - 1;
    Iterator j = last;
    while (true) {
        while (*(++i) < pivot_value);
        while (pivot_value < *(--j)) {
            if (j == first) {
                break;
            }
        }
        if (i >= j) {
            return j;
        }
        std::swap(*i, *j);
    }
}

template<typename Iterator>
void median_quick_sort(Iterator first, Iterator last) {
    if (first < last - 1) {
        Iterator pivot = partition3(first, last - 1);
        median_quick_sort(first, pivot + 1);
        median_quick_sort(pivot + 1, last);
    }
}


//quicksort
template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {
    auto pivot = *last;
    auto i = first - 1;
    for (auto j = first; j < last; ++j) {
        if (*j < pivot) {
            i++;
            std::swap(*i, *j);
        }
    }
    std::swap(*(i + 1), *last);
    return i + 1;
}

template<typename Iterator>
void quick_sort(Iterator first, Iterator last) {
    if (first < last) {
        auto pivot = partition(first, last - 1);
        quick_sort(first, pivot);
        quick_sort(pivot + 1, last);
    }
}

// Standard Library Sort
template<typename Iterator>
void std_sort(Iterator first, Iterator last) {
    std::sort(first, last);
}










#endif