#include <iostream>
#include <fstream>
#include <string>
#include "../../Libraries/Array/array.h"

using std::cerr;
using std::endl;
using std::endl;
using std::string;
using std::exception;
using std::ifstream;
using std::ios;

template <typename T>
void merge(T * &A, int low, int mid, int high)
{
    T *B;
    makeArray<T>(B, high - low);
    int h = low, i = low, j = mid + 1;

    while (h <= mid && j < high) {
        if (A[h] <= A[j]) {
            B[i] = A[h]; 
            h += 1;
        }
        else {
            B[i] = A[j];
            j += 1;
        }
        i += 1;
    }

    if (h > mid) {  // has first seq exhausted?
        for (int k = j; k < high; k++) {
            B[i] = A[k];
            i += 1;
        } 
    }
    else {   // second seq has exhausted!
        for (int k = h; k <= mid; k++) {
            B[i] = A[k];
            i += 1;
        }
    }
    for (int i = low; i < high; i++) {
        A[i] = B[i];
    }
}

template <typename T>
void mergeSort(T * &A, int low, int high)
{
    int mid = 0;
    if (low < high) {  // if there is > 1 items (small(p))
        mid = (low + high) / 2;  // divide
        mergeSort(A, low, mid);     // attack
        mergeSort(A, mid+1, high);  // attack
        merge(A, low, mid, high);  // combine solutions
    }     
}

int main(int argc,  char ** argv)
{
    int *A, i = 0;
    string inputFile("data.txt");

    makeArray<int>(A, 10);
    try {
        makeArray<int>(A, 10);
    }
    catch (const exception& e) {
        cerr << "Caught " << e.what() << endl;
    }
    ifstream fin; 
    fin.open(inputFile, ios::in);
    if (fin.is_open()) {
        while (fin >> A[i]) {
            i += 1;
        }
    }
    printArray(A, i);
    return 0;
}
