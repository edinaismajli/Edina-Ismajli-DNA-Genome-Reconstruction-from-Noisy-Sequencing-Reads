#include "assembler.h"
#include "output.h"
#include "read_parser.h"
#include "stats.h"

#include <chrono>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Perdorimi: dna_assembler <reads.fasta|reads.txt> [min_overlap] [kmer] [error_rate] [output.fasta]\n";
        return 1;
    }

    int minimumOverlap = 8;
    int kmerSize = 5;
    double maximumErrorRate = 0.15;
    string outputFile = "assembly.fasta";
    try {
        if (argc > 2) minimumOverlap = stoi(argv[2]);
        if (argc > 3) kmerSize = stoi(argv[3]);
        if (argc > 4) maximumErrorRate = stod(argv[4]);
        if (argc > 5) outputFile = argv[5];
    }
    catch (...) {
        cerr << "Parametrat numerike nuk jane valide.\n";
        return 1;
    }
    if (minimumOverlap < 1 || kmerSize < 1 || maximumErrorRate < 0 || maximumErrorRate > 1) {
        cerr << "Perdori overlap > 0, k-mer > 0 dhe error_rate mes 0 e 1.\n";
        return 1;
    }

    auto start = chrono::steady_clock::now();
    vector<string> reads = loadReads(argv[1]);
    if (reads.empty()) {
        cerr << "Skedari nuk u hap ose nuk permban reads te vlefshme.\n";
        return 1;
    }

    OverlapGraph graph;
    graph.build(reads, minimumOverlap, kmerSize, maximumErrorRate);
    AssemblyResult result = assembleReads(reads, graph);
    auto finish = chrono::steady_clock::now();
    double seconds = chrono::duration<double>(finish - start).count();

    if (!writeFasta(outputFile, result.sequence)) {
        cerr << "Nuk munda ta shkruaj skedarin e daljes.\n";
        return 1;
    }
    cout << "Montimi u ruajt te " << outputFile << "\n";
    printSummary(reads, graph, result, seconds);
    cout << "Shenim: raporti i gabimeve nuk i dallon mutacionet reale nga gabimet e leximit.\n";
    return 0;
}
