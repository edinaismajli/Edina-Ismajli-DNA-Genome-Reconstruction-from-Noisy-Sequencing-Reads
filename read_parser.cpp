#include "read_parser.h"

#include "dna_utils.h"

#include <fstream>

using namespace std;

vector<string> loadReads(const string& fileName) {
    ifstream input(fileName);
    vector<string> reads;
    if (!input) return reads;

    vector<string> lines;
    string line;
    while (getline(input, line)) lines.push_back(line);
    if (lines.empty()) return reads;

    size_t first = 0;
    while (first < lines.size() && lines[first].empty()) ++first;
    if (first == lines.size()) return reads;

    if (lines[first][0] == '@') {
        for (size_t i = first; i + 3 < lines.size(); i += 4) {
            string read = normalizeRead(lines[i + 1]);
            if (!read.empty()) reads.push_back(read);
        }
        return reads;
    }

    if (lines[first][0] == '>') {
        string current;
        for (const string& item : lines) {
            if (!item.empty() && item[0] == '>') {
                if (!current.empty()) reads.push_back(current);
                current.clear();
            }
            else {
                current += normalizeRead(item);
            }
        }
        if (!current.empty()) reads.push_back(current);
        return reads;
    }

    for (const string& item : lines) {
        string read = normalizeRead(item);
        if (!read.empty()) reads.push_back(read);
    }
    return reads;
}
