#include "stats.h"

#include <iostream>

using namespace std;

size_t estimateMemoryBytes(const vector<string>& reads, const OverlapGraph& graph) {
    size_t bytes = reads.capacity() * sizeof(string);
    for (const string& read : reads) bytes += read.capacity();
    bytes += graph.orientedReads.capacity() * sizeof(string);
    for (const string& read : graph.orientedReads) bytes += read.capacity();
    bytes += graph.edges.capacity() * sizeof(vector<GraphEdge>);
    for (const vector<GraphEdge>& list : graph.edges)
        bytes += list.capacity() * sizeof(GraphEdge);
    return bytes;
}

void printSummary(const vector<string>& reads, const OverlapGraph& graph,
    const AssemblyResult& result, double seconds) {
    cout << "Reads te lexuara: " << reads.size() << '\n'
        << "Reads te perfshira ne montim/contigs: " << result.readsUsed << '\n'
        << "Overlaps ne rrugen greedy: " << result.overlapsUsed << '\n'
        << "Kandidate te krahasuara: " << graph.candidateComparisons << '\n'
        << "Gabime te vleresuara ne overlaps: " << result.estimatedErrors << '\n'
        << "Gjatesia e rezultatit: " << result.sequence.size() << " baza\n"
        << "Koha: " << seconds << " sekonda\n"
        << "Memoria e vleresuar per reads/graf: "
        << estimateMemoryBytes(reads, graph) << " bytes\n";
}
