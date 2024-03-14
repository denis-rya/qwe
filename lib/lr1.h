#pragma once

#include <vector>
using namespace std;

struct PairWithIndex {
    int first;
    int second;
    int index;
};

vector<PairWithIndex> findPairs(const vector<int>& arr);