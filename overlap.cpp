#include "overlap.h"

#include <algorithm>
#include <vector>

using namespace std;

int editDistance(const string& first, const string& second) {
    vector<int> previous(second.size() + 1);
    vector<int> current(second.size() + 1);
    for (size_t j = 0; j <= second.size(); ++j) previous[j] = static_cast<int>(j);

    for (size_t i = 1; i <= first.size(); ++i) {
        current[0] = static_cast<int>(i);
        for (size_t j = 1; j <= second.size(); ++j) {
            int substitution = previous[j - 1] + (first[i - 1] != second[j - 1]);
            current[j] = min({ previous[j] + 1, current[j - 1] + 1, substitution });
        }
        previous.swap(current);
    }
    return previous[second.size()];
}

Overlap findBestOverlap(const string& left, const string& right,
    int minimumLength, double maximumErrorRate) {
    Overlap best;
    int limit = min(static_cast<int>(left.size()), static_cast<int>(right.size()));
    for (int length = limit; length >= minimumLength; --length) {
        string suffix = left.substr(left.size() - length);
        string prefix = right.substr(0, length);
        int errors = editDistance(suffix, prefix);
        double rate = static_cast<double>(errors) / length;
        if (rate <= maximumErrorRate) {
            best.length = length;
            best.errors = errors;
            best.quality = 1.0 - rate;
            return best;
        }
    }
    return best;
}
