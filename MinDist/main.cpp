#include <windows.h>
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
mt19937 random_engine;

vector<int> MakeRandomArray(int numElements);
int MinDistance(vector<int> numbers);
int MinDistance2(vector<int> numbers);
string ConvertArrayToString(vector <int> Array);

int main(){
    vector <int> results = {};
    vector<int> results2 = {};
    for(int i=0; i<25; i++){
        results.push_back(MinDistance(MakeRandomArray(100)));
        results2.push_back(MinDistance2(MakeRandomArray(100)));
    }
    cout << ConvertArrayToString(results) << endl;
    cout << ConvertArrayToString(results2) << endl;
    Sleep(60000);
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

int MinDistance(vector<int> numbers){
    int dmin = 9999;
    for(int i=0;i<numbers.size()-1;i++){
        for(int j=0;j<numbers.size()-1;i++){
            if(i!=j&&numbers[i]-numbers[j]){
                dmin = numbers[i]-numbers[j];
            }
        }
    }
    return dmin;
}

int MinDistance2(vector<int> numbers){
    int temp = 0;
    int dmin = 9999;
    for(int i=0;i<numbers.size()-2;i++){
        for(int j=0;j<numbers.size()-1;i++){
            temp = numbers[i] - numbers[j];
            if(temp < dmin){
                dmin = temp;
            }
        }
    }
}
