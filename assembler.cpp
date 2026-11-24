#include "assembler.h"

#include <algorithm>

using namespace std;

AssemblyResult assembleReads(const vector<string>& reads, const OverlapGraph& graph) {
    AssemblyResult result;
    if (reads.empty()) return result;

    int seedRead = 0;
    for (int i = 1; i < static_cast<int>(reads.size()); ++i)
        if (reads[i].size() > reads[seedRead].size()) seedRead = i;

    vector<bool> used(reads.size(), false);
    int currentNode = seedRead * 2;
    used[seedRead] = true;
    result.sequence = graph.orientedReads[currentNode];
    result.readsUsed = 1;

    while (result.readsUsed < static_cast<int>(reads.size())) {
        const GraphEdge* chosen = nullptr;
        for (const GraphEdge& edge : graph.edges[currentNode]) {
            int originalRead = edge.target / 2;
            if (!used[originalRead]) {
                chosen = &edge;
                break;
            }
        }
        if (chosen == nullptr) break;

        const string& nextRead = graph.orientedReads[chosen->target];
        result.sequence += nextRead.substr(chosen->overlap.length);
        used[chosen->target / 2] = true;
        ++result.readsUsed;
        ++result.overlapsUsed;
        result.estimatedErrors += chosen->overlap.errors;
        currentNode = chosen->target;
    }

    // Reads in disconnected graph components are retained as separate contigs.
    for (int i = 0; i < static_cast<int>(reads.size()); ++i) {
        if (used[i]) continue;
        result.sequence += "NNNNN" + reads[i];
        ++result.readsUsed;
    }
    return result;
}
