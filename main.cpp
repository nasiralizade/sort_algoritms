
#include <iostream>
#include <vector>
#include "sort.h"




template<typename T>
void print(T begin, T end) {
    for (auto it = begin; it != end; it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int>data{4,2,5,1,8,6};

    print(data.begin(), data.end());
    selection_sort(data.begin(), data.end());
    print(data.begin(), data.end());

    return 0;
}