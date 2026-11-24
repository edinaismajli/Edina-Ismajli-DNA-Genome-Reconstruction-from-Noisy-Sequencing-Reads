#pragma once#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "overlap_graph.h"

#include <string>
#include <vector>

using namespace std;

struct AssemblyResult {
    string sequence;
    int readsUsed = 0;
    int overlapsUsed = 0;
    int estimatedErrors = 0;
};

AssemblyResult assembleReads(const vector<string>& reads, const OverlapGraph& graph);

#endif

