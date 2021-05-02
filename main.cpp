#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <chrono>
using namespace std::chrono;
using namespace std;

void write(std::vector<int> v) {
    std::ofstream file;
    file.open("../text.txt");
    for(int i=0;i<v.size();++i) {
        file<<v[i]<<std::endl;
    }
    file.close();
}

/*
vector<int> read() {
    ifstream fin("../primes.txt");
    vector<int> data;
    int element;
    while (fin >> element){
        data.push_back(element);
    }
    return data;
}
*/
unsigned long long int maxDivisiblePerfectSquare(unsigned long long int n) {
    long double sqrtOfN;
    sqrtOfN = sqrt(n);
    vector<unsigned long long int> workingSquares;

    for (unsigned long long int i = round(sqrtOfN); i >= 1; i--) {
        unsigned long long int square = i * i;
        if (n % square == 0) {
            workingSquares.push_back(square);
        }

    }
    return workingSquares.front();
}

unsigned long long int S(unsigned long long int n) {
    unsigned long long int total = 0;
    for(unsigned long long int i = 1; i < n+1; i++) {
	    auto start = high_resolution_clock::now();
	    int b = maxDivisiblePerfectSquare(i);
	    auto end = high_resolution_clock::now();
	    auto duration = duration_cast<microseconds>(end - start);
	    cout << "small duration " << duration.count() << endl;
        total += b;
    }
    return total;
}

/*
void fullTest(){
    int totalTime, totalTimeAverage;
    totalTime = 0;
    for(int i = 0; i < 100; i++) {
        auto start = high_resolution_clock::now();
        // cout << maxDivisiblePerfectSquare(100000000000000) << endl;
        cout << "S " << S(10000) << endl;

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "runtime = " << duration.count() << endl;
        totalTime += duration.count();
    }
    totalTimeAverage = totalTime / 100;
    cout << "totalTime Average = " << totalTimeAverage << endl;
}
*/
int main() {
    auto start = high_resolution_clock::now();
    cout << S(1000000) << endl;
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "total duration " << duration.count() << endl;
    return 0;
}