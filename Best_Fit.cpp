#include "item.h"
#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>

using namespace std;

void best_fit_d(const vector<item>& items, vector<int>& assignment, vector<item>& free_space) {
    int n = items.size();
    int bin = 0;
    item cap ;
    cap.d1=1;
    cap.d2=1;
    cap.d3=1;
    cap.d4=1;

    for (int i = 0; i < n; ++i) {
        // cout << items[i].val << endl;
        int j;
        int min_left_bin = -1;
        item min_left = add(cap ,{1,1,1,1,0});

        for (j = 0; j < bin; ++j) {
            if ((less_than(items[i].val , free_space[j]) || less_than(fabs(sub(items[i].val ,free_space[j])) , __DBL_EPSILON__) && less_than(sub(free_space[j] ,items[i].val),min_left)) {
                min_left_bin = j;
                min_left = sub(free_space[j] , items[i].val);
            }
        }

        if (min_left_bin == -1) { // Doesn't fit in any bin => start a new bin
            free_space.push_back(sub(cap , items[i].val));
            assignment[items[i].id] = bin;
            ++bin;
        } else { // Find a bin where it fits tightest
            free_space[min_left_bin] = sub(free_space[min_left_bin],items[i].val) ;
            assignment[items[i].id] = min_left_bin;
        }
    }

    for (int k = 0; k  < free_space.size(); ++k) {
        if (less_than(fabs(free_space[k]) , __DBL_EPSILON__)) {
            free_space[k] = {0,0,0,0,0};
        }
    }
}


// Implementation of best fit decreasing algorithm
void best_fit_decreasing(const vector<item>& items, vector<int>& assignment, vector<item>& free_space) {
   
    sort(items_d.begin(), items_d.end(), comp);
    best_fit_d(items_d, assignment, free_space);
}