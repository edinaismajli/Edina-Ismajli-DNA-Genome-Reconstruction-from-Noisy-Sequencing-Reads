#include "dna_utils.h"

#include <cctype>

using namespace std;

string normalizeRead(const string& text) {
    string result;
    for (char base : text) {
        char upper = static_cast<char>(toupper(static_cast<unsigned char>(base)));
        if (upper == 'A' || upper == 'C' || upper == 'G' || upper == 'T' || upper == 'N')
            result += upper;
    }
    return result;
}

string reverseComplement(const string& read) {
    string result;
    result.reserve(read.size());
    for (auto it = read.rbegin(); it != read.rend(); ++it) {
        if (*it == 'A') result += 'T';
        else if (*it == 'T') result += 'A';
        else if (*it == 'C') result += 'G';
        else if (*it == 'G') result += 'C';
        else result += 'N';
    }
    return result;
}
