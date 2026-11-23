#ifndef OVERLAP_GRAPH_H
#define OVERLAP_GRAPH_H

#include "overlap.h"

#include <string>
#include <vector>

using namespace std;

struct GraphEdge {
    int target;
    Overlap overlap;
};

class OverlapGraph {
public:
    vector<string> orientedReads;
    vector<vector<GraphEdge>> edges;
    long long candidateComparisons = 0;

    void build(const vector<string>& reads, int minimumOverlap,
        int kmerSize, double maximumErrorRate);
};

#endif
#pragma once
