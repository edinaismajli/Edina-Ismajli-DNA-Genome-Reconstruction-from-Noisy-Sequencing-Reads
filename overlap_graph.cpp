#include "overlap_graph.h"

#include "dna_utils.h"

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void OverlapGraph::build(const vector<string>& reads, int minimumOverlap,
    int kmerSize, double maximumErrorRate) {
    orientedReads.clear();
    edges.clear();
    candidateComparisons = 0;

    for (const string& read : reads) {
        orientedReads.push_back(read);
        orientedReads.push_back(reverseComplement(read));
    }
    edges.resize(orientedReads.size());

    unordered_map<string, vector<int>> prefixIndex;
    for (int node = 0; node < static_cast<int>(orientedReads.size()); ++node) {
        int seedLength = min(kmerSize, static_cast<int>(orientedReads[node].size()));
        if (seedLength > 0)
            prefixIndex[orientedReads[node].substr(0, seedLength)].push_back(node);
    }

    for (int source = 0; source < static_cast<int>(orientedReads.size()); ++source) {
        const string& read = orientedReads[source];
        int seedLength = min(kmerSize, static_cast<int>(read.size()));
        if (seedLength == 0) continue;
        string suffixSeed = read.substr(read.size() - seedLength);
        unordered_set<int> candidates;
        auto found = prefixIndex.find(suffixSeed);
        if (found != prefixIndex.end())
            for (int target : found->second) candidates.insert(target);
        if (candidates.empty())
            for (int target = 0; target < static_cast<int>(orientedReads.size()); ++target)
                candidates.insert(target);

        for (int target : candidates) {
            if (source == target || source / 2 == target / 2) continue;
            ++candidateComparisons;
            Overlap overlap = findBestOverlap(read, orientedReads[target],
                minimumOverlap, maximumErrorRate);
            if (overlap.length > 0) edges[source].push_back({ target, overlap });
        }
        sort(edges[source].begin(), edges[source].end(), [](const GraphEdge& a, const GraphEdge& b) {
            if (a.overlap.length != b.overlap.length)
                return a.overlap.length > b.overlap.length;
            return a.overlap.quality > b.overlap.quality;
            });
    }
}
