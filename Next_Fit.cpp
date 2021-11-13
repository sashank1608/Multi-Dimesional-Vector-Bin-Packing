#include <cmath>
#include <iostream>

using namespace std;

// Implementation of next_fit algorithm
void next_fit(const vector<item>& items, vector<int>& assignment, vector<item>& free_space) {
    int n = items.size();
    int bin = 0;
    item cap ;
    cap.d1=1;
    cap.d2=1;
    cap.d3=1;
    cap.d4=1;
    item fre = cap;

    for (int i = 0; i < n; ++i) {
        if (less_than(items[i] , fre) || less_than(fabs(sub(items[i],fre)) , __DBL_EPSILON__)) {
            assignment[i] = bin;
            fre =sub(fre,items[i]);
        } else {
            ++bin;
            assignment[i] = bin;
            free_space.push_back(less_than(fabs(fre) , __DBL_EPSILON__) ? 0.0 : fre);
            fre = sub(cap , items[i]);
        }
    }
    if (less_than_eq(__DBL_EPSILON__,fabs(sub(fre , cap)))) { // NOT_EQUAL
        free_space.push_back(less_than(fabs(fre) , __DBL_EPSILON__) ? 0.0 : fre);
    }
}