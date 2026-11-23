#ifndef OVERLAP_H
#define OVERLAP_H

#include <string>

using namespace std;

struct Overlap {
    int length = 0;
    int errors = 0;
    double quality = 0.0;
};

int editDistance(const string& first, const string& second);
Overlap findBestOverlap(const string& left, const string& right,
    int minimumLength, double maximumErrorRate);

#endif
#pragma once
