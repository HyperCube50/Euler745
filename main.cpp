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

int maxDivisiblePerfectSquare(int n) {
    double sqrtOfN;
    sqrtOfN = sqrt(n);
    // cout << sqrtOfN << endl;
    vector<int> workingSquares;
    for(int i = 1; i < sqrtOfN+1; i++) {
        // cout << "i = " <<  i << endl;
        // cout << "i*i = " << i*i << endl;
        if(n%(i*i)==0) {
            workingSquares.push_back((i*i));
            // cout << "working" << endl;
        }
        if(i >= sqrtOfN) {
            // cout << workingSquares.back() << " is the end of the vector..." << endl;
            return workingSquares.back();
        }
    }
    cout << "if we got this far, shit is fucked up" << endl;
    return 0;
}

int S(int n) {
    int total = 0;
    for(int i = 1; i < n+1; i++) {
        total += maxDivisiblePerfectSquare(i);
    }
    return total;
}
int main() {
    auto start = high_resolution_clock::now();
    // cout << maxDivisiblePerfectSquare(100) << endl;
    cout << S(100000000000000) << endl;


    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << duration.count() << endl;
    return 0;
}