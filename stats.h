#ifndef STATS_H
#define STATS_H

#include "assembler.h"

#include <cstddef>
#include <vector>

using namespace std;

size_t estimateMemoryBytes(const vector<string>& reads, const OverlapGraph& graph);
void printSummary(const vector<string>& reads, const OverlapGraph& graph,
    const AssemblyResult& result, double seconds);

#endif
