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

unsigned long long int total;
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

void threadObject(unsigned long long int threadI, unsigned long long int n) {
	for(unsigned long long int i = threadI; i < n+1; i++) {
		auto start = high_resolution_clock::now();
		unsigned long long int b = maxDivisiblePerfectSquare(i);
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		mtx.lock();
		cout << duration.count() << endl;
		total += b;
		mtx.unlock();
	}
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

    unsigned long long int threadN;
    unsigned long long int extra;
    unsigned long long int bigN;
    bigN = 100000000000000;
	// divide by 12 for the twelve threads
	threadN = bigN / 12;
	extra = bigN % 12;

	// start the threads
	thread t0   (threadObject, threadN*0 +1, threadN);
	thread t1   (threadObject, threadN*1 +1, threadN*2);
	thread t2   (threadObject, threadN*2 +1, threadN*3);
	thread t3   (threadObject, threadN*3 +1, threadN*4);
	thread t4   (threadObject, threadN*4 +1, threadN*5);
	thread t5   (threadObject, threadN*5 +1, threadN*6);
	thread t6   (threadObject, threadN*6 +1, threadN*7);
	thread t7   (threadObject, threadN*7 +1, threadN*8);
	thread t8   (threadObject, threadN*8 +1, threadN*9);
	thread t9   (threadObject, threadN*9 +1, threadN*10);
	thread t10  (threadObject, threadN*10+1, threadN*11);
	thread t11  (threadObject, threadN*11+1, threadN*12);

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
	for(unsigned long long int i = threadN*12+1; i < threadN*12+extra+1; i++) {
		unsigned long long int b = maxDivisiblePerfectSquare(i);
		total += b;
	}


    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "total = " << total << endl;
    cout << "total duration " << duration.count() << endl;
    return 0;
}