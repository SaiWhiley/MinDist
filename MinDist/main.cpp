#define __USE_MINGW_ANSI_STDIO 0
#include <windows.h>
#include <limits>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <math.h>
#include <tuple>
#include <random>

using namespace std;
using namespace std::chrono;


vector<int> MakeRandomArray(int numElements);
tuple<float,long> MinDistance(vector<int> numbers);
tuple<float, long> MinDistance2(vector<int> numbers);
tuple<float, float> MinDistTIME(vector<int> numbers);
tuple<float, float> MinDist2TIME(vector<int> numbers);
void runBasicOperations(int increments, int trials);
void runTimeElapsed(int increments, int trials);
string ConvertArrayToString(vector <int> Array);

typedef vector<tuple<float,int>>listOfOperationResults;
typedef vector<tuple<float,float>>listOfTimeResults;

int main(){
    cout << "Assessment 1: MinDist | Liam Abel n9467874 & Sai Whiley n9454829" << endl;
    //runBasicOperations(100, 10);
    runTimeElapsed(1000, 1);

}

void runTimeElapsed(int increments, int trials){
    int numValues = 0;
    vector<int> results = {};
    vector<int> results2 = {};
    float totalRuntimeONE;
    float meanRuntimeONE;
    float totalRuntimeTWO;
    float meanRuntimeTWO;

    listOfTimeResults timeResults1;
    listOfTimeResults timeResults2;

    ofstream resultsStream;
    resultsStream.open("timeResults.csv", fstream::app);
    resultsStream << ",Mean Time Elapsed, \r";
    resultsStream << "Array Size, ONE, TWO";

    for(int i = 0; i < increments; i++){
        numValues +=10;
        timeResults1.clear();
        timeResults2.clear();
        totalRuntimeONE = 0;
        meanRuntimeONE =0;
        totalRuntimeTWO=0;
        meanRuntimeTWO=0;

        for(int j = 0; j < trials; j++){
            timeResults1.emplace_back(MinDistTIME(MakeRandomArray(numValues)));
            timeResults2.emplace_back(MinDist2TIME(MakeRandomArray(numValues)));
        }
        for(auto &n : timeResults1){
            totalRuntimeONE += get<1>(n);
        }
        for(auto &n : timeResults2){
            totalRuntimeTWO += get<1>(n);
        }
        meanRuntimeONE = totalRuntimeONE/trials;
        meanRuntimeTWO = totalRuntimeTWO/trials;

        resultsStream << "\r" << numValues << "," << meanRuntimeONE << "," << meanRuntimeTWO;
    }

}

void runBasicOperations(int increments, int trials){
    int numValues = 0;
    long operationsTotalONE;
    long meanOperationsONE;
    long operationsTotalTWO;
    long meanOperationsTWO;

    listOfOperationResults opResults1;
    listOfOperationResults opResults2;

    ofstream resultsStream;
    resultsStream.open("results.csv", fstream::app);
    resultsStream << ",MeanOperations,\r";
    resultsStream << "Array Size, ONE, TWO";
    for(int i = 0; i < increments; i++){
        numValues +=10;
        opResults1.clear();
        opResults2.clear();
        meanOperationsONE = 0;
        operationsTotalONE = 0;
        meanOperationsTWO = 0;
        operationsTotalTWO = 0;

        for(int j = 0; j < trials; j++){
            opResults1.emplace_back(MinDistance(MakeRandomArray(numValues)));
            opResults2.emplace_back(MinDistance2(MakeRandomArray(numValues)));
        }
        for(auto &n : opResults1){
            operationsTotalONE += get<1>(n);
        }
        for(auto &n : opResults2){
            operationsTotalTWO += get<1>(n);
        }
        meanOperationsONE = operationsTotalONE/trials;
        meanOperationsTWO = operationsTotalTWO/trials;

        resultsStream << "\r" << numValues << "," << meanOperationsONE << "," << meanOperationsTWO;



    }
}


string ConvertArrayToString(vector <int> Array){
    string result = "";
    for(int i =0;i<Array.size();i++){
        result += to_string(Array[i]);
    }
    return result;
}

vector<int> MakeRandomArray(int numElements){
    mt19937 random_engine(time(0));
    vector<int> testArray;
    for(int i=0; i<numElements; i++){
        testArray.push_back(random_engine()%100);
    }
    return testArray;
}

tuple<float,long> MinDistance(vector<int> numbers){  //takes vector and returns <minDist, Operations>
    long int basicOperations = 0;
    double dmin = numeric_limits<double>::max();
    for(int i=0;i<numbers.size()-1;i++){
        for(int j=0;j<numbers.size()-1;j++){
            basicOperations+= 2;
            if(i!=j&&abs(numbers[i]-numbers[j]) < dmin){ //2 comparison operations
                dmin = abs(numbers[i]-numbers[j]);
            }
        }
    }
    cout << "array size: " << numbers.size() << " mindist: " << dmin << " basic operations: " << basicOperations <<endl;
    return make_tuple(dmin, basicOperations);
}

tuple<float, long> MinDistance2(vector<int> numbers){ //takes ve4c
    long int basicOperations = 0;
    double temp = 0;
    double dmin = numeric_limits<double>::max();
    for(int i=0;i<numbers.size()-2;i++){
        for(int j=0;j<numbers.size()-1;j++){
            temp = abs(numbers[i] - numbers[j]);
            basicOperations++;
            if(temp < dmin){
                dmin = temp;
            }
        }
    }
    return make_tuple(dmin, basicOperations);
}

tuple<float, float> MinDistTIME(vector<int> numbers){
    double dmin = numeric_limits<double>::max();
    duration<double> timeElapsed;
    steady_clock::time_point startTime  = steady_clock::now();
    for(int i=0;i<numbers.size()-1;i++){
        for(int j=0;j<numbers.size()-1;j++){
            if(i!=j&&abs(numbers[i]-numbers[j]) < dmin){ //2 comparison operations
                dmin = abs(numbers[i]-numbers[j]);
            }
        }
    }
    steady_clock::time_point endTime = steady_clock::now();
    timeElapsed = duration_cast<duration<double>>(endTime - startTime);
    cout << "array size: " << numbers.size() << " mindist: " << "time taken: " << timeElapsed.count() << endl;
    return make_tuple(dmin, timeElapsed.count());
}

tuple<float, float> MinDist2TIME(vector<int> numbers){
    double temp = 0;
    double dmin = numeric_limits<double>::max();
    duration<double> timeElapsed;
    steady_clock::time_point startTime = steady_clock::now();
    for(int i=0;i<numbers.size()-2;i++){
        for(int j=0;j<numbers.size()-1;j++){
            temp = abs(numbers[i] - numbers[j]);
            if(temp < dmin){
                dmin = temp;
            }
        }
    }
    steady_clock::time_point endTime = steady_clock::now();
    timeElapsed = duration_cast<duration<double>>(endTime - startTime);
    return make_tuple(dmin, timeElapsed.count());
}
