#ifndef GENERATE_H
#define GENERATE_H
void generate_random(std::vector<int>&data){
    std::generate(data.begin(), data.end(),std::rand);
}
void generate_constant(std::vector<int>&data){
    int number=rand()%99+1;
    std::fill(data.begin(), data.end(),number);
}
void generate_increasing(std::vector<int>&data){
    int number=rand()%99+1;
    for (int &i:data) {
        i=number;
        number++;
    }
}
void generate_decreasing(std::vector<int>&data){
    int number=data.size();
    for (int &i:data) {
        i=number;
        number--;
    }
}

#endif GENERATE_H