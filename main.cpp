#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <thread>
#include <algorithm>
#include <numeric>
#include <mutex>
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

uint64_t total;
mutex mtx;

/*void write(std::vector<int> v) {
    std::ofstream file;
    file.open("../text.txt");
    for(int i=0;i<v.size();++i) {
        file<<v[i]<<std::endl;
    }
    file.close();
}*/

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

vector<uint64_t> squareGen(uint64_t n) {
	vector<uint64_t> returnSquares;
	for (uint64_t i = 1; i*i-1 < n; i++) {
		returnSquares.push_back(i*i);
	}
	return returnSquares;
}

uint64_t maxDivisiblePerfectSquare(uint64_t n, vector<uint64_t> squaresList) {
    long double sqrtOfN;
    sqrtOfN = sqrt(n);
    vector<uint64_t> workingSquares;

    for (uint64_t i : squaresList) {
        if (n % i == 0) {
            workingSquares.push_back(i);
        }

    }
    return workingSquares.back();
}

void threadObject(uint64_t threadI, uint64_t n, vector<uint64_t> squares) {
	for(uint64_t i = threadI; i < n+1; i++) {
		auto start = high_resolution_clock::now();
		uint64_t b = maxDivisiblePerfectSquare(i, squares);
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		mtx.lock();
		cout << i << " " << duration.count() << endl;
		total += b;
		mtx.unlock();
	}
}


int main() {
    auto start = high_resolution_clock::now();

    uint64_t threadN;
    uint64_t extra;
    uint64_t bigN;
    vector<uint64_t> squares;
    bigN = 1000000;

    // generate squares
    squares = squareGen(bigN);

    // divide by 12 for the twelve threads
	threadN = bigN / 12;
	extra = bigN % 12;

	// start the threads
	thread t0   (threadObject, threadN*0 +1, threadN, squares);
	thread t1   (threadObject, threadN*1 +1, threadN*2, squares);
	thread t2   (threadObject, threadN*2 +1, threadN*3, squares);
	thread t3   (threadObject, threadN*3 +1, threadN*4, squares);
	thread t4   (threadObject, threadN*4 +1, threadN*5, squares);
	thread t5   (threadObject, threadN*5 +1, threadN*6, squares);
	thread t6   (threadObject, threadN*6 +1, threadN*7, squares);
	thread t7   (threadObject, threadN*7 +1, threadN*8, squares);
	thread t8   (threadObject, threadN*8 +1, threadN*9, squares);
	thread t9   (threadObject, threadN*9 +1, threadN*10, squares);
	thread t10  (threadObject, threadN*10+1, threadN*11, squares);
	thread t11  (threadObject, threadN*11+1, threadN*12, squares);

	// wait for them to finish
	t0 .join();
	t1 .join();
	t2 .join();
	t3 .join();
	t4 .join();
	t5 .join();
	t6 .join();
	t7 .join();
	t8 .join();
	t9 .join();
	t10.join();
	t11.join();

	// left overs
	for(uint64_t i = threadN*12+1; i < threadN*12+extra+1; i++) {
		uint64_t b = maxDivisiblePerfectSquare(i, squares);
		total += b;
	}


    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "total = " << total << endl;
    cout << "total duration " << duration.count() << endl;
    return 0;
}