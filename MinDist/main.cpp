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
mt19937 random_engine(time(0));

vector<int> MakeRandomArray(int numElements);
tuple<float,long> MinDistance(vector<int> numbers);
tuple<float, long> MinDistance2(vector<int> numbers);
string ConvertArrayToString(vector <int> Array);

typedef vector<tuple<float,int>>listOfOperationResults;

int main(){
    cout << "Assessment 1: MinDist | Liam Abel n9467874 & Sai Whiley n9454829" << endl;
    vector <int> results = {};
    vector<int> results2 = {};
    int numValues = 0;
    int increments = 100;
    int trials = 10;
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
            basicOperations++;
            if(i!=j&&abs(numbers[i]-numbers[j]) < dmin){
                dmin = abs(numbers[i]-numbers[j]);
            }
        }
    }
    cout << "array size: " << numbers.size() << " mindist: " << dmin << " basic operations: " << basicOperations <<endl;
    return make_tuple(dmin, basicOperations);
}

tuple<float, long> MinDistance2(vector<int> numbers); //takes ve4c
(vector<int> numbers){
    long int basicOperations = 0;
    double temp = 0;
    double dmin = numeric_limits<double>::max();
    for(int i=0;i<numbers.size()-2;i++){
        for(int j=0;j<numbers.size()-1;j++){
            basicOperations++;
            temp = abs(numbers[i] - numbers[j]);
            if(temp < dmin){
                basicOperations++;
                dmin = temp;
            }
        }
    }
    return make_tuple(dmin, basicOperations);
}
