#include "Algorithms.h"

std::size_t linearSearch(const std::vector<std::string>& reads,
                         const std::string& target) {
    for (std::size_t i = 0; i < reads.size(); ++i) {
        if (reads[i] == target) {
            return i;
        }
    }

    return reads.size();
}
