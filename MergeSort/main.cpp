#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "MergeSort.h"

using namespace std;

int main() {

    vector<int> x ={4,2,1,3};
    vector<string> y = {"hola","fa","z","zaz","a","b",","};

    MergeSort::MergeSort(x);
    MergeSort::MergeSort(y);
    
    for(auto &i : x ){
        cout<<i<<" ";
    }
    cout<<endl;
    for(auto &i : y ){
        cout<<i<<" ";
    }
    return 0;
}