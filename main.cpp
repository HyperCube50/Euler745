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

vector<int> read() {
    ifstream fin("../primes.txt");
    vector<int> data;
    int element;
    while (fin >> element){
        data.push_back(element);
    }
    return data;
}

long int maxDivisiblePerfectSquare(long int n) {
    long double sqrtOfN;
    sqrtOfN = sqrt(n);
    vector<long int> workingSquares;

    for (long int i = round(sqrtOfN); i >= 1; i--) {
        long int square = i * i;
        if (n % square == 0) {
            workingSquares.push_back(square);
        }

    }
    return workingSquares.front();
}

long int S(long int n) {
    long int total = 0;
    for(long int i = 1; i < n+1; i++) {
        auto start = high_resolution_clock::now();
        total += maxDivisiblePerfectSquare(i);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << i << " took " << duration.count() << endl;
    }
    return total;
}

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

int main() {
    cout << S(100000000000000) << endl;
    return 0;
}