//
// Created by Juan Galvez on 2020-04-07.
//

#ifndef MERGESORT_MERGESORT_H
#define MERGESORT_MERGESORT_H

#endif //MERGESORT_MERGESORT_H

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

namespace MergeSort {

    template<typename Tipo>
    void Sort(vector<Tipo> &left, vector<Tipo> &right, vector<Tipo> &bars) {

        int nL = left.size();
        int nR = right.size();
        int i = 0; // index merged subarray
        int j = 0; // index first subarray
        int k = 0; // index second subarray

        while (j < nL && k < nR) {
            if (left[j] < right[k]) {
                bars[i] = left[j];
                j++;
            } else {
                bars[i] = right[k];
                k++;
            }
            i++;
        }

        /* Copy the remaining elements of left[], if there
       are any */

        while (j < nL) {
            bars[i] = left[j];
            j++;
            i++;
        }

        /* Copy the remaining elements of right[], if there
       are any */

        while (k < nR) {
            bars[i] = right[k];
            k++;
            i++;
        }
    }

    template<typename Tipo>
    void MergeSort(vector<Tipo> &bar) {
        if (bar.size() <= 1) return;

        int mid = bar.size() / 2;

        vector<Tipo> left;
        vector<Tipo> right;

        for (size_t j = 0; j < mid; j++)
            left.push_back(bar[j]);
        for (size_t j = 0; j < (bar.size()) - mid; j++)
            right.push_back(bar[mid + j]);

        MergeSort(left);
        MergeSort(right);
        Sort(left, right, bar);
    }
}
