#include "item.h"
#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>

using namespace std;
// Implementation of first fit algorithm

void first_fit_d(const vector<item>& items, vector<int>& assignment, vector<item>& free_space) {
    int n = items.size();
    int bin = 0;
    item cap ;
    cap.d1=1;
    cap.d2=1;
    cap.d3=1;
    cap.d4=1;

    for (int i = 0; i < n; ++i) {
        int j;
        for (j = 0 ; j < bin; ++j) {
            if (less_than(items[i] , free_space[j]) || less_than(fabs(sub(items[i] - free_space[j])) , __DBL_EPSILON__)) {
                free_space[j] =sub(free_space[j],items[i]) ;
                assignment[items[i].id] = j;
                break;
            }
        }
        if (j == bin) { 
            free_space.push_back(sub(cap - items[i].val));
            assignment[items[i].id] = bin;
            ++bin;
        }
    }

    for (int k = 0; k  < free_space.size(); ++k) {
        if (less_than(fabs(free_space[k]) , __DBL_EPSILON__)) {
            free_space[k] = {0,0,0,0,0};
        }
    }
}


// Implementation of first fit decreasing algorithm
void first_fit_decreasing(const vector<item>& items, vector<int>& assignment, vector<item>& free_space) {
   
    sort(items_d.begin(), items_d.end(), comp);
    first_fit_d(items_d, assignment, free_space);
}